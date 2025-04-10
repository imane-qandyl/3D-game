/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:26:04 by lalwafi           #+#    #+#             */
/*   Updated: 2025/04/10 20:27:49 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int key_pressed(int key, t_game *game)
{
	if (key == ESC)
		finish(game, 0);
	if (key == W)
		move_player(game, 0, -4);
	if (key == A)
		move_player(game, -4, 0);
	if (key == S)
		move_player(game, 0, 4);
	if (key == D)
		move_player(game, 4, 0);
	if (key == LEFT)
	{
		game->angle += 1;
		if (game->angle >= 360)
			game->angle -= 360;
		get_end_of_vector(game->player_x, game->player_y, game->angle);
	}
	if (key == RIGHT)	
	{
		game->angle -= 1;
		if (game->angle < 0)
			game->angle += 360;
		get_end_of_vector(game->player_x, game->player_y, game->angle);
	}
	return (0);
}

void	move_player(t_game *game, int px, int py)
{
	int	x;
	int	y;
	
	x = -1;
	y = -1;
	if ((game->player_y + py) >= (game->map_height * TILE_SIZE - 4) || \
	(game->player_x + px) >= (game->map_width * TILE_SIZE - 4))
	return ;
	while (++y < 4)
	{
		while (++x < 4)
		{
			// printf("1 : %f\n", ((game->player_x + x) / TILE_SIZE));
			if (game->map[(int)((game->player_y + y) / TILE_SIZE)][(int)((game->player_x + x) / TILE_SIZE)] == '1')
				mlx_pixel_put(game->mlx, game->win, game->player_x + x, game->player_y + y, 0xFF0000);
			else
				mlx_pixel_put(game->mlx, game->win, game->player_x + x, game->player_y + y, 0xAAAAAA);
			mlx_pixel_put(game->mlx, game->win,\
						game->player_x + x + px,\
						game->player_y + y + py, 0xFFFF00);
		}
		x = -1;
	}
	game->player_x += px;
	game->player_y += py;
}

void	get_end_of_vector(float px, float py, double angle)
{
	float	lx;
	float	ly;
	float	lz;
	float	new_px;
	float	new_py;

	printf("px = %f\npy = %f\nangle = %f\nweird = %f\n", px,py,angle, (px/TILE_SIZE));
	if (angle > 0 && angle < 90)
	{
		lx = TILE_SIZE - px;
		ly = lx * tanf(angle * PI/180);
		lz = lx / cosf(angle * PI/180);
		new_px = px + lx;
		new_py = py - ly;
	}
	else if (angle > 90 && angle < 180)
	{
		lx = px;
		ly = lx * tanf(angle * PI/180);
		lz = lx / cosf(angle * PI/180);
		new_px = px - lx;
		new_py = py - ly;
	}
	else if (angle > 180 && angle < 270)
	{
		lx = px;
		ly = lx * tanf(angle * PI/180);
		lz = lx / cosf(angle * PI/180);
		new_px = px - lx;
		new_py = py + ly;
	}
	else
	{
		lx = TILE_SIZE - px;
		ly = lx * tanf(angle * PI/180);
		lz = lx / cosf(angle * PI/180);
		new_px = px + lx;
		new_py = py + ly;
	}
	printf("lx = %f\nly = %f\nlz = %f\nnew_px = %f\nnew_py = %f\n", lx,ly,lz,new_px,new_py);
}