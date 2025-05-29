/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 02:22:38 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/26 03:21:18 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rendering_2d(t_game *game)
{
	double	ray_angle;
	double	next_ray;
	int		i;
	t_point	end_point;

	i = WIN_WIDTH;
	ray_angle = game->angle + 30;
	next_ray = 60.0 / WIN_WIDTH;
	init_point(&end_point);
	while (--i >= 0)
	{
		end_point.ray_num = i;
		end_point = raycast_v_h(game, ray_angle);
		dda(game, end_point);
		ray_angle -= next_ray;
		if (ray_angle < 0)
			ray_angle += 360;
	}
}

void	dda(t_game *game, t_point end)
{
	int		i;
	double	steps;
	double	x_increment;
	double	y_increment;

	i = -1;
	if (fabs(end.x - game->p.x) > fabs(end.y - game->p.y))
	{
		steps = fabs(end.x - game->p.x);
		x_increment = (end.x - game->p.x) / steps;
		y_increment = (end.y - game->p.y) / steps;
	}
	else
	{
		steps = fabs(end.y - game->p.y);
		x_increment = (end.x - game->p.x) / steps;
		y_increment = (end.y - game->p.y) / steps;
	}
	while (++i <= steps)
		my_mlx_pixel_put(&game->img, game->p.x + (x_increment * i),
			game->p.y + (y_increment * i), 0x00FFFF);
}
