/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:32:20 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/07 05:12:00 by lalwafi          ###   ########.fr       */
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

	i = 0; // change back to 0, i just want the lines on the map for now
	while (i < TILE_SIZE)
	{
		j = 0; // change back to 0 also
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(&game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_2d(t_game *game)
{
	int	y;
	int	x;
	
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
								&game->img.endian);
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
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	draw_player(t_game *game)
{
	my_mlx_pixel_put(&game->img, game->p.px, \
		game->p.py, 0xFFFF00);
	my_mlx_pixel_put(&game->img, game->p.px + 1, \
		game->p.py, 0xFFFF00);
	my_mlx_pixel_put(&game->img, game->p.px, \
		game->p.py + 1, 0xFFFF00);
	my_mlx_pixel_put(&game->img, game->p.px + 1, \
		game->p.py + 1, 0xFFFF00);
	// draw_ray_5px(game);
	dda_thing(game);
}

void	draw_3d(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
								&game->img.endian);
	draw_background(game, 0x84c8d1, 0x1f5c2c);
	dda_only_3d(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
void	draw_ray_5px(t_game *game)
{
	float	dx;
	float	dy;
	int		i;

	dx = game->pdx;
	dy = game->pdy;
	
	i = 10;
	while (i-- > 0)
	{
		my_mlx_pixel_put(&game->img, game->p.px + dx, \
			game->p.py + dy, 0x0000FF);
		dx += game->pdx;
		dy += game->pdy;
	}
}
