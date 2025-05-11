/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:49:10 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/08 14:59:58 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_point	round_endpoint(t_point ph, int angle)
{
	if (angle > 0 && angle < 180)
		ph.py = ceilf(ph.py);
	else
		ph.py = floorf(ph.py);
	if (angle > 270 || angle < 90)
		ph.px = ceilf(ph.px);
	else
		ph.px = floorf(ph.px);
	return (ph);
}

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
	t_point	temp;
	t_point	comp;

	dx = cosf(angle * PI/180);
	dy = sinf(angle * PI/180);
	temp.px = game->p.px;
	temp.py = game->p.py;
	comp = round_endpoint(temp, angle);
	// while ((int)temp.px != (int)point.px || (int)temp.py != (int)point.py)
	while (comp.px != point.px || comp.py != point.py)
	{
		if (temp.py > WIN_HEIGHT || temp.px > WIN_WIDTH || temp.py < 0 || temp.px < 0 || \
			(int)((temp.py)/TILE_SIZE) >= game->map_height || \
			(int)((temp.px)/TILE_SIZE) >= game->map_width)
			break ;
		// printf("----------ray---------\ndx = %f\ndy = %f\npointx = %f\npointy = %f\n----------ray---------\n", temp.px, temp.py, point.px, point.py);
		my_mlx_pixel_put(&game->img, temp.px, temp.py, color);
		temp.px += dx;
		temp.py += dy;
		comp = round_endpoint(temp, angle);
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
	while ((dy + ph.py) <= WIN_HEIGHT && (dx + ph.px) <= WIN_WIDTH && 
		(dy + ph.py) >= 0 && (dx + ph.px) >= 0)
	{
		if (game->map[(int)((dy + ph.py)/TILE_SIZE)][(int)((dx + ph.px)/TILE_SIZE)] == '1')
			break ;
		ph.px = (dx + ph.px);
		ph.py = (dy + ph.py);
	}
	ph.length = sqrtf((fabsf(game->p.px - ph.px) * fabsf(game->p.px - ph.px)) + 
				(fabsf(game->p.py - ph.py) * fabsf(game->p.py - ph.py)));
	ph = round_endpoint(ph, angle);
	// printf("----- just raycast ----- final phpy = %f     phpx = %f\n", ph.py, ph.px);
	return (ph);
}

void	dda_thing(t_game *game)
{
	int		i;
	t_point	end;
	
	i = 30;
	while (i >= -30)
	{
		end = just_raycast_custom_angle(game, (game->angle + i));
		draw_ray_custom_angle(game, end, (game->angle + i), 0x00FFFF);
		// draw_line(game, end, i + 30, 0x090c66);
		i--;
	}
}


// void	dda(t_game *game, t_point end, int color)
// {
// 	float	z;
// 	float	dy;
// 	float	dx;
// 	int		i;

// 	z = sqrtf((end.px * end.px) + (end.py * end.py));
// 	dx = (end.px - game->p.px) / z;
// 	dy = (end.py - game->p.py) / z;
// 	i = -1;
// 	while (i++ <= z)
// 	{
// 		my_mlx_pixel_put(&game->img, game->p.px + ((i - 1)*dx), game->p.py + ((i - 1)*dy), color);
// 	}
// }
