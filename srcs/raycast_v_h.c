/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_v_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 05:59:28 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/20 06:44:38 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_point	raycast_horizontal(t_game *game, double ray_angle)
{
	t_point	end; // the point where the ray lands
	double	increment_x;
	double	increment_y;

	init_point(&end);
	end.angle = ray_angle;
	end.dx = cos(ray_angle * PI/180);
	end.dy = sin(ray_angle * PI/180);
	increment_x = 0;
	increment_y = 0;
	if (fabs(ray_angle - 180) < 0.000001 || fabs(ray_angle - 360) < 0.000001 || fabs(ray_angle) <= 0.000001)
	{
		end.length = 999999;
		return (end);
	}
	if (end.dy < 0)
	{
		end.y = (int)(game->p.y/TILE_SIZE) * TILE_SIZE - 0.0001;
		increment_y = -1 * TILE_SIZE;
	}
	else
	{
		end.y = (int)(game->p.y/TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		increment_y = TILE_SIZE;
	}

	if (end.dx < 0)
	{
		end.x = game->p.x + (fabs(end.y - game->p.y) / tan(ray_angle * (PI/180)));
		increment_x = (increment_y/tan(ray_angle*(PI/180))); 
	}
	else
	{
		end.x = game->p.x + (fabs(end.y - game->p.y) / tan(ray_angle * (PI/180)));
		increment_x = (increment_y/tan(ray_angle*(PI/180))); 
	}

	printf("before horizontal x     = %f\n", end.x);
	printf("before horizontal y     = %f\n", end.y);
	printf("before horizontal increment_x = %f\n", increment_x);
	printf("before horizontal increment_y = %f\n", increment_y);
	printf("before horizontal angle = %f\n\n", ray_angle);

	while ((int)(end.y/TILE_SIZE) < game->map_height && (int)(end.x/TILE_SIZE) < game->map_width &&
			(int)(end.y/TILE_SIZE) >= 0 && (int)(end.x/TILE_SIZE) >= 0 && 
			game->map[(int)(end.y/TILE_SIZE)][(int)(end.x/TILE_SIZE)] != '1')
	{
		end.x += increment_x;
		end.y += increment_y;
	}
	end.length = sqrt((end.x - game->p.x) * (end.x - game->p.x) + 
						(end.y - game->p.y) * (end.y - game->p.y));
	
	printf("after  horizontal x     = %f\n", end.x);
	printf("after  horizontal y     = %f\n", end.y);
	printf("after  horizontal increment_x = %f\n", increment_x);
	printf("after  horizontal increment_y = %f\n", increment_y);
	printf("after  horizontal angle = %f\n\n", ray_angle);
	return (end);
}

t_point	raycast_vertical(t_game *game, double ray_angle)
{
	t_point	end; // the point where the ray lands
	double	increment_x;
	double	increment_y;

	init_point(&end);
	end.angle = ray_angle;
	end.dx = cos(ray_angle * PI/180);
	end.dy = sin(ray_angle * PI/180);
	increment_x = 0;
	if (fabs(ray_angle - 270) < 0.000001 || fabs(ray_angle - 90) < 0.000001)
	{
		end.length = 999999;
		return (end);
	}
	if (end.dx < 0)
	{
		end.x = (int)(game->p.x/TILE_SIZE) * TILE_SIZE - 0.0001;
		increment_x = -1 * TILE_SIZE;
	}
	else
	{
		end.x = (int)(game->p.x/TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		increment_x = TILE_SIZE;
	}

	if (end.dy < 0)
	{
		end.y = game->p.y + (fabs(end.x - game->p.x) * tan(ray_angle * (PI/180)));
		increment_y = (increment_x*tan(ray_angle*(PI/180))); 
	}
	else
	{
		end.y = game->p.y + (fabs(end.x - game->p.x) * tan(ray_angle * (PI/180)));
		increment_y = (increment_x*tan(ray_angle*(PI/180))); 
	}

	printf("before vertical x     = %f\n", end.x);
	printf("before vertical y     = %f\n", end.y);
	printf("before vertical increment_x = %f\n", increment_x);
	printf("before vertical increment_y = %f\n", increment_y);
	printf("before vertical angle = %f\n\n", ray_angle);

	while ((int)(end.y/TILE_SIZE) < game->map_height && (int)(end.x/TILE_SIZE) < game->map_width &&
			(int)(end.y/TILE_SIZE) >= 0 && (int)(end.x/TILE_SIZE) >= 0 && 
			game->map[(int)(end.y/TILE_SIZE)][(int)(end.x/TILE_SIZE)] != '1')
	{
		end.x += increment_x;
		end.y += increment_y;
	}
	end.length = sqrt((end.x - game->p.x) * (end.x - game->p.x) + 
						(end.y - game->p.y) * (end.y - game->p.y));
	
	printf("after  vertical x     = %f\n", end.x);
	printf("after  vertical y     = %f\n", end.y);
	printf("after  vertical increment_x = %f\n", increment_x);
	printf("after  vertical increment_y = %f\n", increment_y);
	printf("after  vertical angle = %f\n\n", ray_angle);
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
		printf("----------VERTICAL------------\n");
		return (v);
	}
	printf("----------HORIZONTAL------------\n");
	return (h);
}
