/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3d_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:51:27 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/29 21:15:38 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

int	rgb_to_hex(int red, int green, int blue)
{
	return (((red & 0xff) << 16) | ((green & 0xff) << 8) | (blue & 0xff));
}

void	draw_background_3d(t_game *game, int ceiling, int floor)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y < (WIN_HEIGHT / 2))
				my_mlx_pixel_put(&game->img, x, y, ceiling);
			else
				my_mlx_pixel_put(&game->img, x, y, floor);
		}
	}
}

void	init_point(t_point *point)
{
	point->angle = 0.0;
	point->dx = 0.0;
	point->dy = 0.0;
	point->face = '0';
	point->length = 0.0;
	point->ray_num = 0;
	point->x = 0.0;
	point->y = 0.0;
}
