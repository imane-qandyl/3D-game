/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_v_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 05:59:28 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/26 03:18:45 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	raycast_horizontal_2(t_game *game, t_point *end, double ray_angle)
{
	double	increment_x;
	double	increment_y;

	increment_x = 0;
	increment_y = 0;
	if (end->dy < 0)
	{
		end->y = (int)(game->p.y / TILE_SIZE) * TILE_SIZE - 0.0001;
		increment_y = -1 * TILE_SIZE;
	}
	else
	{
		end->y = (int)(game->p.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		increment_y = TILE_SIZE;
	}
	end->x = game->p.x + ((end->y - game->p.y) / tan(ray_angle * (PI / 180)));
	increment_x = (increment_y / tan(ray_angle * (PI / 180)));
	while ((int)(end->y / TILE_SIZE) < game->map_height &&
		(int)(end->x / TILE_SIZE) < game->map_width &&
		(int)(end->y / TILE_SIZE) >= 0 && (int)(end->x / TILE_SIZE) >= 0 &&
		game->map[(int)(end->y / TILE_SIZE)][(int)(end->x / TILE_SIZE)] != '1')
	{
		end->x += increment_x;
		end->y += increment_y;
	}
}

t_point	raycast_horizontal(t_game *game, double ray_angle)
{
	t_point	end;

	init_point(&end);
	end.angle = ray_angle;
	end.dx = cos(ray_angle * PI / 180);
	end.dy = sin(ray_angle * PI / 180);
	if (fabs(ray_angle - 180) < 0.000001 || fabs(ray_angle - 360) < 0.000001
		|| fabs(ray_angle) <= 0.000001)
	{
		end.length = 999999;
		return (end);
	}
	raycast_horizontal_2(game, &end, ray_angle);
	end.length = sqrt((end.x - game->p.x) * (end.x - game->p.x)
			+ (end.y - game->p.y) * (end.y - game->p.y));
	end.length *= cosf((game->angle - ray_angle) * PI / 180);
	if (end.dy > 0.000001f)
		end.face = 'N';
	else
		end.face = 'S';
	return (end);
}

static void	raycast_vertical_2(t_game *game, t_point *end, double ray_angle)
{
	double	increment_x;
	double	increment_y;

	increment_x = 0;
	increment_y = 0;
	if (end->dx < 0)
	{
		end->x = (int)(game->p.x / TILE_SIZE) * TILE_SIZE - 0.0001;
		increment_x = -1 * TILE_SIZE;
	}
	else
	{
		end->x = (int)(game->p.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		increment_x = TILE_SIZE;
	}
	end->y = game->p.y + ((end->x - game->p.x) * tan(ray_angle * (PI / 180)));
	increment_y = (increment_x * tan(ray_angle * (PI / 180)));
	while ((int)(end->y / TILE_SIZE) < game->map_height &&
		(int)(end->x / TILE_SIZE) < game->map_width &&
		(int)(end->y / TILE_SIZE) >= 0 && (int)(end->x / TILE_SIZE) >= 0 &&
		game->map[(int)(end->y / TILE_SIZE)][(int)(end->x / TILE_SIZE)] != '1')
	{
		end->x += increment_x;
		end->y += increment_y;
	}
}

t_point	raycast_vertical(t_game *game, double ray_angle)
{
	t_point	end;

	init_point(&end);
	end.angle = ray_angle;
	end.dx = cos(ray_angle * PI / 180);
	end.dy = sin(ray_angle * PI / 180);
	if (fabs(ray_angle - 270) < 0.000001 || fabs(ray_angle - 90) < 0.000001)
	{
		end.length = 999999;
		return (end);
	}
	raycast_vertical_2(game, &end, ray_angle);
	end.length = sqrt((end.x - game->p.x) * (end.x - game->p.x)
			+ (end.y - game->p.y) * (end.y - game->p.y));
	end.length *= cosf((game->angle - ray_angle) * PI / 180);
	if (end.dx > 0.000001f)
		end.face = 'W';
	else
		end.face = 'E';
	return (end);
}

t_point	raycast_v_h(t_game *game, double ray_angle)
{
	t_point	v;
	t_point	h;

	v = raycast_vertical(game, ray_angle);
	h = raycast_horizontal(game, ray_angle);
	if (v.length < h.length)
	{
		return (v);
	}
	return (h);
}
