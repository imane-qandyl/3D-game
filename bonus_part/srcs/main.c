/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:06:21 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/29 21:15:38 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

static void	cleanup_and_exit(t_game *game, char *error_msg)
{
	if (error_msg)
		printf("Error : %s\n", error_msg);
	if (game)
	{
		if (game->map)
		{
			free_map(game->map);
			game->map = NULL;
		}
		if (game->mlx && game->win)
		{
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		game->mlx = NULL;
	}
	exit(1);
}

static void	parse(t_game *game, char *map_path)
{
	t_error	err;

	init_map_info(game);
	err = parse_file(map_path, game);
	if (err != ERR_NONE)
	{
		print_error(err);
		cleanup_and_exit(game, "Failed parsing map file");
	}
	exec_init(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		cleanup_and_exit(game, "Failed to initialize MLX");
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->win)
		cleanup_and_exit(game, "Failed to create window");
	if (!load_textures(game))
		cleanup_and_exit(game, "Failed to load textures");
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	parse(&game, argv[1]);
	make_texture_maps(&game);
	draw_3d(&game);
	get_minimap_tile_size(&game);
	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 1L << 0, finish, &game);
	mlx_loop_hook(game.mlx, movement, &game);
	mlx_loop(game.mlx);
	return (0);
}

int	finish(t_game *game, int i)
{
	cleanup_and_exit(game, NULL);
	return (i);
}
