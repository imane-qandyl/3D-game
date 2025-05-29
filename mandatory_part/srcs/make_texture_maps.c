/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_texture_maps.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 01:46:20 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/29 19:17:24 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	make_no_texture_map(t_game *game, int x, int y)
{
	int		bbp;
	int		size_line;
	int		endian;
	char	*pixels;

	pixels = mlx_get_data_addr(game->no_texture, &bbp, &size_line, &endian);
	y = -1;
	while (++y < game->tex_height)
	{
		x = -1;
		while (++x < game->tex_width)
		{
			game->no_tex_map[y][x] = (*(int *)(pixels
						+ (y * size_line) + (x * (bbp / 8)))) & 0x00FFFFFF;
		}
	}
}

static void	make_so_texture_map(t_game *game, int x, int y)
{
	int		bbp;
	int		size_line;
	int		endian;
	char	*pixels;

	pixels = mlx_get_data_addr(game->so_texture, &bbp, &size_line, &endian);
	y = -1;
	while (++y < game->tex_height)
	{
		x = -1;
		while (++x < game->tex_width)
		{
			game->so_tex_map[y][x] = (*(int *)(pixels
						+ (y * size_line) + (x * (bbp / 8)))) & 0x00FFFFFF;
		}
	}
}

static void	make_ea_texture_map(t_game *game, int x, int y)
{
	int		bbp;
	int		size_line;
	int		endian;
	char	*pixels;

	pixels = mlx_get_data_addr(game->ea_texture, &bbp, &size_line, &endian);
	y = -1;
	while (++y < game->tex_height)
	{
		x = -1;
		while (++x < game->tex_width)
		{
			game->ea_tex_map[y][x] = (*(int *)(pixels
						+ (y * size_line) + (x * (bbp / 8)))) & 0x00FFFFFF;
		}
	}
}

static void	make_we_texture_map(t_game *game, int x, int y)
{
	int		bbp;
	int		size_line;
	int		endian;
	char	*pixels;

	pixels = mlx_get_data_addr(game->we_texture, &bbp, &size_line, &endian);
	y = -1;
	while (++y < game->tex_height)
	{
		x = -1;
		while (++x < game->tex_width)
		{
			game->we_tex_map[y][x] = (*(int *)(pixels
						+ (y * size_line) + (x * (bbp / 8)))) & 0x00FFFFFF;
		}
	}
}

void	make_texture_maps(t_game *game)
{
	make_no_texture_map(game, -1, -1);
	make_so_texture_map(game, -1, -1);
	make_ea_texture_map(game, -1, -1);
	make_we_texture_map(game, -1, -1);
}
