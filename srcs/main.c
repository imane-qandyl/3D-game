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

int	get_angle(char c)
{
	if (c == 'S')
		return (90);
	if (c == 'W')
		return (180);
	if (c == 'N')
		return (270);
	if (c == 'E')
		return (0);
	write(1, "this shouldnt show\n", 19);
	return (0);
}

static void cleanup_and_exit(t_game *game, char *error_msg)
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

void temp_init_for_exec(t_game *game)
{
	init_point(&game->p);
	game->player_dir = get_player_direction(game);
	game->angle = get_angle(game->player_dir);
	get_player_position(game);  // Use local variables
	// game->dx = cos(game->p.x) * 5;
	// game->dy = sin(game->p.y) * 5;
	game->dx = cos(game->angle * PI/180);
	game->dy = sin(game->angle * PI/180);
	game->key.w = false;
	game->key.a = false;
	game->key.s = false;
	game->key.d = false;
	game->key.left = false;
	game->key.right = false;
	game->img.img = NULL;
}

int load_textures(t_game *game)
{
	int width, height;

	game->no_texture = mlx_xpm_file_to_image(game->mlx, game->no_texture, &width, &height);
	if (!game->no_texture)
		return (0);

	game->tex_width = width;
	game->tex_height = height;

	game->so_texture = mlx_xpm_file_to_image(game->mlx, game->so_texture, &width, &height);
	if (!game->so_texture || width != game->tex_width || height != game->tex_height)
		return (0);

	game->we_texture = mlx_xpm_file_to_image(game->mlx, game->we_texture, &width, &height);
	if (!game->we_texture || width != game->tex_width || height != game->tex_height)
		return (0);
	
	game->ea_texture = mlx_xpm_file_to_image(game->mlx, game->ea_texture, &width, &height);
	if (!game->ea_texture || width != game->tex_width || height != game->tex_height)
		return (0);
	
	return (1);
}

static void	texture_test(t_game *game)
{
	int		bits_per_ppixel;
	int		size_line;
	int		endian;
	char	*pixels;
	int		y;
	int		x;
	int		color;

	pixels = mlx_get_data_addr(game->no_texture, &bits_per_ppixel, &size_line, &endian);
	y = -1;
	while (++y < game->tex_height)
	{
		x = -1;
		while (++x < game->tex_width)
		{
			color = (*(int *)(pixels + (y * size_line) + (x * (bits_per_ppixel / 8)))) & 0x00FFFFFF;
			game->no_tex_map[y][x] = color;
		}
	}
	pixels = mlx_get_data_addr(game->so_texture, &bits_per_ppixel, &size_line, &endian);
	y = -1;
	while (++y < game->tex_height)
	{
		x = -1;
		while (++x < game->tex_width)
		{
			color = (*(int *)(pixels + (y * size_line) + (x * (bits_per_ppixel / 8)))) & 0x00FFFFFF;
			game->so_tex_map[y][x] = color;
		}
	}
	pixels = mlx_get_data_addr(game->ea_texture, &bits_per_ppixel, &size_line, &endian);
	y = -1;
	while (++y < game->tex_height)
	{
		x = -1;
		while (++x < game->tex_width)
		{
			color = (*(int *)(pixels + (y * size_line) + (x * (bits_per_ppixel / 8)))) & 0x00FFFFFF;
			game->ea_tex_map[y][x] = color;
		}
	}
	pixels = mlx_get_data_addr(game->we_texture, &bits_per_ppixel, &size_line, &endian);
	y = -1;
	while (++y < game->tex_height)
	{
		x = -1;
		while (++x < game->tex_width)
		{
			color = (*(int *)(pixels + (y * size_line) + (x * (bits_per_ppixel / 8)))) & 0x00FFFFFF;
			game->we_tex_map[y][x] = color;
		}
	}
}


int main(int argc, char **argv)
{
	t_game game;
	t_error err;
	ft_bzero(&game, sizeof(t_game));

	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	// Initialize game structure
	init_map_info(&game);
	err = parse_file(argv[1], &game);
	if (err != ERR_NONE)
	{
		print_error(err);
		cleanup_and_exit(&game, "Failed parsing map file");
	}
	// Initialize MLX
	temp_init_for_exec(&game);
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

	int j = -1;
	while (game.map[++j])
		printf("(%s)\n", game.map[j]);



	texture_test(&game);
	// game.p.x = 655.292893;
	// game.p.y = 99.452273;
	// game.angle = 225.000000;


	// Draw the map
	draw_3d(&game);
	// draw_2d(&game);
	
	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game); // key release
	mlx_hook(game.win, 17, 1L << 0, finish, &game);
	mlx_loop_hook(game.mlx, movement, &game);
	mlx_loop(game.mlx);
	return (0);
}

int finish(t_game *game, int i)
{
	cleanup_and_exit(game, NULL);
	return (i);
}
