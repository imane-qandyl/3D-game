/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:49:10 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/19 21:27:08 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_point	round_endpoint(t_point end, int angle)
{
	if (angle > 0 && angle < 180)
	end.py = ceilf(end.py);
	else
	end.py = floorf(end.py);
	if (angle > 270 || angle < 90)
	end.px = ceilf(end.px);
	else
	end.px = floorf(end.px);
	return (end);
}

float	get_length_of_ray(t_point game, t_point end)
{
	float	length_x;
	float	length_y;

	length_x = fabsf((end.px - game.px)/end.dx);
	length_y = fabsf((end.py - game.py)/end.dy);
	if (length_x < length_y)
		return (length_x);
	return (length_y);
}

t_point	raycast_custom_angle(t_game *game, float angle)
{
	float	dx;
	float	dy;
	t_point	end;
	float	dist_x;
	float	dist_y;

	dx = cosf(angle * PI/180);
	dy = sinf(angle * PI/180);
	end.px = game->p.px;
	end.py = game->p.py;
	end.dx = dx;
	end.dy = dy;
	end.angle = angle;
	dist_x = 0;
	dist_y = 0;
	while ((dy + end.py) >= 0.000001f && (dx + end.px) >= 0.000001f)
	{
		if (game->map[(int)((end.py + dy)/TILE_SIZE)][(int)((end.px)/TILE_SIZE)] == '1' && 
		game->map[(int)((end.py)/TILE_SIZE)][(int)((end.px + dx)/TILE_SIZE)] == '1')
		{
			dist_x += dx;
			dist_y += dy;
			if (dist_x <= dist_y)
			{
				if (dx > 0.000001f)
					end.face = 'W';
				else
					end.face = 'E';
			}
			else
			{
				if (dy > 0.000001f)
					end.face = 'N';
				else
					end.face = 'S';
			}
			break ;
		}
		else if (game->map[(int)((end.py + dy)/TILE_SIZE)][(int)((end.px)/TILE_SIZE)] == '1')
		{
			dist_x += dx;
			dist_y += dy;
			if (dy > 0.000001f)
				end.face = 'N';
			else
				end.face = 'S';
			break ;
		}
		else if (game->map[(int)((end.py)/TILE_SIZE)][(int)((end.px + dx)/TILE_SIZE)] == '1')
		{
			dist_y += dy;
			dist_x += dx;
			if (dx > 0.000001f)
				end.face = 'W';
			else
				end.face = 'E';
			break ;
		}
		// if (game->map[(int)((dy + end.py)/TILE_SIZE)][(int)((dx + end.px)/TILE_SIZE)] == '1')
		// 	break ;
		dist_x += dx;
		dist_y += dy;
		end.px = (end.px + dx);
		end.py = (end.py + dy);
	}
	// end = round_endpoint(end, angle);
	end.length = sqrtf(((dist_x) * (dist_x)) + 
				((dist_y) * (dist_y)));
	// end.length = get_length_of_ray(game->p, end);
	// end.length = end.length * cosf((game->angle - angle) * PI/180);
	
	// printf("----- just raycast -----     %f\n", angle);
	// printf("px         = %f\n", game->p.px);
	// printf("py         = %f\n", game->p.py);
	// printf("end.px     = %f\n", end.px);
	// printf("end.py     = %f\n", end.py);
	// printf("x          = %d\n", (int)((end.px)/TILE_SIZE));
	// printf("y  	       = %d\n", (int)((end.py)/TILE_SIZE));
	printf("distx      = %f\n", dist_x);
	printf("disty      = %f\n", dist_y);
	// printf("dx         = %f\n", dx);
	// printf("dy         = %f\n", dy);
	// printf("game angle = %f\n", game->angle);
	// printf("angle      = %f\n", end.angle);
	printf("length     = %f\n", end.length);
	// printf("face       = %c\n", end.face);
	// printf("map_height = %d\n", game->map_height);
	// printf("map_width  = %d\n", game->map_width);
	// printf("----- just raycast -----\n");
	return (end);
}
