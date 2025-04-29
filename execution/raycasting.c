/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:49:10 by lalwafi           #+#    #+#             */
/*   Updated: 2025/04/29 14:30:33 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_point just_raycast(t_game *game)
{
	t_point	ph;
	// float	tempx;
	// float	tempy;

	// ph.px = WIN_WIDTH;
	// ph.py = WIN_HEIGHT;
	ph.px = game->p.px;
	ph.py = game->p.py;
	while (game->map[(int)((game->pdy + ph.py)/TILE_SIZE)][(int)((game->pdx + ph.px)/TILE_SIZE)] != '1')
	{
		ph.px = (game->pdx + ph.px);
		ph.py = (game->pdy + ph.py);
	}
	printf("----- just raycast ----- final phpy = %f     phpx = %f\n", ph.py, ph.px);
	return (ph);
}

t_point	which_ray_shorter(t_game *game, t_point ph, t_point pv)
{
	float	lh;
	float	lv;

	lh = fabsf(game->p.px - ph.px) + fabsf(game->p.py - ph.py);
	lv = fabsf(game->p.px - pv.px) + fabsf(game->p.py - pv.py);
	if (lh <= lv)
		return (ph);
	return (pv);
}

void	draw_ray(t_game *game, t_point point, int color)
{
	float	dx;
	float	dy;

	dx = game->pdx + game->p.px;
	dy = game->pdy + game->p.py;
	
	while ((int)dx != (int)point.px || (int)dy != (int)point.py)
	{
		if (dy > WIN_HEIGHT || dx > WIN_WIDTH || dy < 0 || dx < 0 || \
			(int)((dy)/TILE_SIZE) >= game->map_height || \
			(int)((dx)/TILE_SIZE) >= game->map_width)
			break ;
		// printf("----------ray---------\ndx = %f\ndy = %f\npointx = %f\npointy = %f\n----------ray---------\n", dx, dy, point.px, point.py);
		my_mlx_pixel_put(&game->img, dx, dy, color);
		dx += game->pdx;
		dy += game->pdy;
	}
}

void	draw_ray_custom_angle(t_game *game, t_point point, int angle, int color)
{
	float	dx;
	float	dy;
	float	x;
	float	y;

	dx = cosf(angle * PI/180);
	dy = sinf(angle * PI/180);
	x = game->p.px;
	y = game->p.py;
	
	while ((int)x != (int)point.px || (int)y != (int)point.py)
	{
		if (y > WIN_HEIGHT || x > WIN_WIDTH || y < 0 || x < 0 || \
			(int)((y)/TILE_SIZE) >= game->map_height || \
			(int)((x)/TILE_SIZE) >= game->map_width)
			break ;
		// printf("----------ray---------\ndx = %f\ndy = %f\npointx = %f\npointy = %f\n----------ray---------\n", x, y, point.px, point.py);
		my_mlx_pixel_put(&game->img, x, y, color);
		x += dx;
		y += dy;
	}
}

t_point	just_raycast_custom_angle(t_game *game, int angle)
{
	float	dx;
	float	dy;
	t_point	ph;

	dx = cosf(angle * PI/180);
	dy = sinf(angle * PI/180);
	ph.px = game->p.px;
	ph.py = game->p.py;
	
	while (game->map[(int)((dy + ph.py)/TILE_SIZE)][(int)((dx + ph.px)/TILE_SIZE)] != '1')
	{
		ph.px = (dx + ph.px);
		ph.py = (dy + ph.py);
	}
	// printf("----- just raycast ----- final phpy = %f     phpx = %f\n", ph.py, ph.px);
	return (ph);
}

void	dda_thing(t_game *game)
{
	// draw_ray(game, which_ray_shorter(game, horizontal_raycast(game), vertical_raycast(game)), 0x0000FF);
	// dda(game, which_ray_shorter(game, horizontal_raycast(game), vertical_raycast(game)), 0x0000FF);
	// draw_ray(game, horizontal_raycast(game), 0x0000FF);
	// draw_ray(game, vertical_raycast(game), 0x00FFFF);
	int	i;
	i = 30;
	while (i >= -30)
	{
		draw_ray_custom_angle(game, just_raycast_custom_angle(game, (game->angle + i)),(game->angle + i), 0x00FFFF);
		i--;
	}
}

void	dda(t_game *game, t_point end, int color)
{
	float	z;
	float	dy;
	float	dx;
	int		i;

	z = sqrtf((end.px * end.px) + (end.py * end.py));
	dx = (end.px - game->p.px) / z;
	dy = (end.py - game->p.py) / z;
	i = -1;
	while (i++ <= z)
	{
		my_mlx_pixel_put(&game->img, game->p.px + ((i - 1)*dx), \
			game->p.py + ((i - 1)*dy), color);
	}
}
