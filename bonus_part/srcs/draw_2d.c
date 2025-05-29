/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:31:21 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/29 21:15:38 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((y) >= WIN_HEIGHT || (x) >= WIN_WIDTH || (y) < 0.000001
		|| (x) < 0.000001)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

void	draw_2d(t_game *game)
{
	int	y;
	int	x;

	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel, &game->img.line_length,
			&game->img.endian);
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_square(game, x * TILE_SIZE, y * TILE_SIZE, 0xFF0000);
			else
				draw_square(game, x * TILE_SIZE, y * TILE_SIZE, 0xAAAAAA);
			x++;
		}
		y++;
	}
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	draw_player(t_game *game)
{
	my_mlx_pixel_put(&game->img, game->p.x,
		game->p.y, 0xFFFF00);
	my_mlx_pixel_put(&game->img, game->p.x + 1,
		game->p.y, 0xFFFF00);
	my_mlx_pixel_put(&game->img, game->p.x,
		game->p.y + 1, 0xFFFF00);
	my_mlx_pixel_put(&game->img, game->p.x + 1,
		game->p.y + 1, 0xFFFF00);
	rendering_2d(game);
}
