/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:27:43 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/29 19:51:11 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    get_minimap_tile_size(t_game *game)
{
	if (game->map_height > game->map_width)
		game->minimap_tile_size = (WIN_HEIGHT / 4)/(game->map_height);
	else
		game->minimap_tile_size = (WIN_WIDTH / 4)/(game->map_width);
	// printf("tile size = %d\nmap height = %d\nmap width = %d\nminimap tile size = %d\n", TILE_SIZE, game->map_height, game->map_width, game->minimap_tile_size);
}

void	draw_minimap_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->minimap_tile_size)
	{
		j = 0;
		while (j < game->minimap_tile_size)
		{
			my_mlx_pixel_put(&game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_minimap_square(game, x * game->minimap_tile_size, y * game->minimap_tile_size, 0x8c2eff);
			else
				draw_minimap_square(game, x * game->minimap_tile_size, y * game->minimap_tile_size, 0xAAAAAA);
			x++;
		}
		y++;
	}
	draw_minimap_player(game);
}

void	draw_minimap_player(t_game *game)
{
	int	x;
	int	y;

	x = (game->p.x / TILE_SIZE) * game->minimap_tile_size;
	y = (game->p.y / TILE_SIZE) * game->minimap_tile_size;
	my_mlx_pixel_put(&game->img, x,
		y, 0xFFFF00);
	my_mlx_pixel_put(&game->img, x + 1,
		y, 0xFFFF00);
	my_mlx_pixel_put(&game->img, x,
		y + 1, 0xFFFF00);
	my_mlx_pixel_put(&game->img, x + 1,
		y + 1, 0xFFFF00);
	// rendering_2d(game);
}
