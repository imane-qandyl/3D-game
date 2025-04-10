/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:32:20 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/08 10:19:45 by imqandyl         ###   ########.fr       */
/*   Updated: 2025/04/09 20:05:38 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	void *texture;

	// If it's a wall (color is red), determine which texture to use based on position
	if (color == 0xFF0000)
	{
		// Default to north texture
		texture = game->no_texture;
		
		// Check surrounding cells to determine wall orientation
		if (y/TILE_SIZE + 1 < game->map_height && game->map[y/TILE_SIZE + 1][x/TILE_SIZE] == '0')
			texture = game->so_texture;
		else if (x/TILE_SIZE + 1 < game->map_width && game->map[y/TILE_SIZE][x/TILE_SIZE + 1] == '0')
			texture = game->ea_texture;
		else if (x/TILE_SIZE > 0 && game->map[y/TILE_SIZE][x/TILE_SIZE - 1] == '0')
			texture = game->we_texture;

		mlx_put_image_to_window(game->mlx, game->win, texture, x, y);
		return;
	}

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(game->mlx, game->win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
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
				draw_square(game, x * TILE_SIZE, y * TILE_SIZE, 0xFF0000); // Red wall
			else
				draw_square(game, x * TILE_SIZE, y * TILE_SIZE, 0xAAAAAA); // Grey floor
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *game)
{
	int	x;
	int	y;
	
	x = -1;
	y = -1;
	while (++y < 4)
	{
		while (++x < 4)
		{
			mlx_pixel_put(game->mlx, game->win,\
						game->player_x + x,\
						game->player_y + y, 0xFFFF00);
		}
		x = -1;
	}
}
