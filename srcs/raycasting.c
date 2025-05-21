/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:49:10 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/21 17:30:16 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_point	round_endpoint(t_point end, int angle)
{
	if (angle > 0 && angle < 180)
		end.y = ceilf(end.y);
	else
		end.y = floorf(end.y);
	if (angle > 270 || angle < 90)
		end.x = ceilf(end.x);
	else
		end.x = floorf(end.x);
	return (end);
}

static bool	check_both_intersect(t_game *game, t_point *end, double dist_x, double dist_y)
{
	if (game->map[(int)((end->y + end->dy)/TILE_SIZE)][(int)((end->x)/TILE_SIZE)] == '1' && 
		game->map[(int)((end->y)/TILE_SIZE)][(int)((end->x + end->dx)/TILE_SIZE)] == '1')
	{
		if (dist_x <= dist_y)
		{
			if (end->dx > 0.000001f)
				end->face = 'W';
			else
				end->face = 'E';
		}
		else
		{
			if (end->dy > 0.000001f)
				end->face = 'N';
			else
				end->face = 'S';
		}
		return (true);
	}
	return (false);
}

static bool	check_y(t_game *game, t_point *end)
{
	if (game->map[(int)((end->y + end->dy)/TILE_SIZE)][(int)((end->x)/TILE_SIZE)] == '1')
	{
		if (end->dy > 0.000001f)
			end->face = 'N';
		else
			end->face = 'S';
		return (true);
	}
	return (false);
}

static bool	check_x(t_game *game, t_point *end)
{
	if (game->map[(int)((end->y)/TILE_SIZE)][(int)((end->x + end->dx)/TILE_SIZE)] == '1')
	{
		if (end->dx > 0.000001f)
			end->face = 'W';
		else
			end->face = 'E';
		return (true);
	}
	return (false);
}

t_point	raycast(t_game *game, double ray_angle)
{
	t_point	end; // the point where the ray lands
	double	dist_x;
	double	dist_y;

	dist_x = 0;
	dist_y = 0;
	init_point(&end);
	end.angle = ray_angle;
	end.dx = cos(ray_angle * PI/180);
	end.dy = sin(ray_angle * PI/180);
	end.x = game->p.x;
	end.y = game->p.y;
	while (end.x >= 0 && end.y >= 0)
	{
		dist_x += end.dx;
		dist_y += end.dy;
		if (check_both_intersect(game, &end, dist_x, dist_y) == true ||
			check_x(game, &end) == true ||
			check_y(game, &end) == true)
			break;
		end.x += end.dx;
		end.y += end.dy;
	}
	round_endpoint(end, end.angle);
	end.length = sqrtf(((dist_x) * (dist_x)) + 
						((dist_y) * (dist_y)));
	printf("raycast  x     = %.15f\n", end.x);
	printf("raycast  y     = %.15f\n", end.y);
	printf("raycast  dx    = %.15f\n", end.dx);
	printf("raycast  dy    = %.15f\n", end.dy);
	printf("raycast  angle = %.15f\n\n", ray_angle);
	return (end);
}

void	draw_wall_line(t_game *game, t_point end, int location)
{
	double	line_height;
	int		line_location;

	if(end.length < 5.0f)
		line_height = WIN_WIDTH;
	else
		line_height = ((WIN_WIDTH*TILE_SIZE)/end.length);
	if (line_height > WIN_WIDTH)
		line_height = WIN_WIDTH;
	line_location = -line_height + (line_height/2);
	while (line_height-- > 0)
	{
		if (end.face == 'N')
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0xec8df8);
		else if (end.face == 'S')
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0x62106d);
		else if (end.face == 'E')
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0xda20f1);
		else if (end.face == 'W')
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0x69516c);
		else
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0x000000);
	}
}
