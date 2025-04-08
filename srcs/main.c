/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:19:23 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/08 10:19:15 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void cleanup_and_exit(t_game *game, char *error_msg)
{
	if (error_msg)
		printf("Error\n%s\n", error_msg);
	if (game->map)
		free_map(game->map);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(1);
}

static int load_textures(t_game *game)
{
	int width, height;

	// Load north texture
	game->no_texture = mlx_xpm_file_to_image(game->mlx, game->no_texture, &width, &height);
	if (!game->no_texture)
		return (0);
	game->tex_width = width;
	game->tex_height = height;

	// Load south texture
	game->so_texture = mlx_xpm_file_to_image(game->mlx, game->so_texture, &width, &height);
	if (!game->so_texture || width != game->tex_width || height != game->tex_height)
		return (0);

	// Load west texture
	game->we_texture = mlx_xpm_file_to_image(game->mlx, game->we_texture, &width, &height);
	if (!game->we_texture || width != game->tex_width || height != game->tex_height)
		return (0);

	// Load east texture
	game->ea_texture = mlx_xpm_file_to_image(game->mlx, game->ea_texture, &width, &height);
	if (!game->ea_texture || width != game->tex_width || height != game->tex_height)
		return (0);

	return (1);
}

int main(int argc, char **argv)
{
	t_game game;
	t_error err;

	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}

	// Initialize game structure
	init_map_info(&game);

	// Parse the map file
	err = parse_file(argv[1], &game);
	if (err != ERR_NONE)
	{
		print_error(err);
		free_map_info(&game);
		return (1);
	}

	// Load the map
	game.map = read_map(argv[1]);
	if (!game.map)
		cleanup_and_exit(&game, "Failed to load map");

	// Initialize MLX
	game.mlx = mlx_init();
	if (!game.mlx)
		cleanup_and_exit(&game, "Failed to initialize MLX");

	// Create window
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game.win)
		cleanup_and_exit(&game, "Failed to create window");

	// Load textures
	if (!load_textures(&game))
		cleanup_and_exit(&game, "Failed to load textures");

	// Draw the map
	draw_map(&game);

	// Start the game loop
	mlx_loop(game.mlx);

	// Cleanup (this won't be reached due to mlx_loop)
	free_map_info(&game);
	return (0);
}
