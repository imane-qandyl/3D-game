/* ************************************************************************** */ 
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:19:23 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/09 19:06:21 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	temp_init_for_exec(t_game *game)
{
		// char *map[7] = {"111111" , "100001" , "1000P1" , "100001" , "100001" , "111111"};
	// game.map = map;
	game->player_x = 4 * TILE_SIZE + (TILE_SIZE / 2);
	game->player_y = 2 * TILE_SIZE + (TILE_SIZE / 2);
	game->player_dx = cos(game->player_x) * 5;
	game->player_dy = sin(game->player_y) * 5;
	game->map_height = 6;
	game->map_width = 6;
	printf("dx = %f\n", game->player_dx);
}

int	main(void)
{
	t_game	game;

	game.map = read_map("maps/level1.cub");
	if (!game.map)
	{
		printf("Failed to load map.\n");
		return (1);
	}
	temp_init_for_exec(&game);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	draw_map(&game);
	draw_player(&game);
	mlx_hook(game.win, 2, 0, key_pressed, &game);
	mlx_hook(game.win, 17, 0, finish, &game);
	mlx_loop(game.mlx);
	return (0);
}

int	finish(t_game *game, int i)
{
	mlx_destroy_window(game->mlx, game->win);
	free_map(game->map);
	exit(i);
	return (i);
}
