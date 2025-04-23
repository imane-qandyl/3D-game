/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:32:20 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/23 08:08:11 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((y) >= WIN_HEIGHT || (x) >= WIN_WIDTH || \
		(y) < 0 || (x) < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(&game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
					&game->img.line_length, &game->img.endian);

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
	my_mlx_pixel_put(&game->img, game->player_x, \
		game->player_y, 0xFFFF00);
	draw_ray_10px(game, 10, 0x0000FF);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	draw_ray_10px(t_game *game, int pixels, unsigned int color)
{
	float	dx;
	float	dy;

	dx = game->pdx;
	dy = game->pdy;
	
	while (pixels-- > 0)
	{
		my_mlx_pixel_put(&game->img, game->player_x + dx, \
			game->player_y + dy, color);
		dx += game->pdx;
		dy += game->pdy;
	}
}
