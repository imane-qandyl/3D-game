/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:26:04 by lalwafi           #+#    #+#             */
/*   Updated: 2025/04/11 19:05:23 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int key_pressed(int key, t_game *game)
{
	if (key == ESC)
		finish(game, 0);
	// if (key == W)
	// 	move_player(game, game->pdx, game->pdy);
	// if (key == A)
	// 	move_player(game, change_angle(game->angle, 270, 1), change_angle(game->angle, 270, 2));
	// if (key == S)
	// 	move_player(game, change_angle(game->angle, 180, 1), change_angle(game->angle, 180, 2));
	// if (key == D)
	// 	move_player(game, change_angle(game->angle, 90, 1), change_angle(game->angle, 90, 2));
	if (key == W)
		move_player_1px(game, 1, game->pdx, game->pdy);
	if (key == A)
		move_player_1px(game, 1, change_angle(game->angle, 270, 1), change_angle(game->angle, 270, 2));
	if (key == S)
		move_player_1px(game, 1, change_angle(game->angle, 180, 1), change_angle(game->angle, 180, 2));
	if (key == D)
		move_player_1px(game, 1, change_angle(game->angle, 90, 1), change_angle(game->angle, 90, 2));
	if (key == LEFT)
	{
		game->angle -= 5;
		if (game->angle >= 360)
			game->angle -= 360;
		game->pdx = cosf(game->angle * PI/180);
		game->pdy = sinf(game->angle * PI/180);
		// get_end_of_vector(game->player_x, game->player_y, game->angle * (PI/180));
		draw_ray_5px(game);
	}
	if (key == RIGHT)	
	{
		game->angle += 5;
		if (game->angle < 0)
			game->angle += 360;	
		game->pdx = cosf(game->angle * PI/180);
		game->pdy = sinf(game->angle * PI/180);
		// get_end_of_vector(game->player_x, game->player_y, game->angle * (PI/180));
		draw_ray_5px(game);
	}
	return (0);
}

void	draw_ray_5px(t_game *game)
{
	float	dx;
	float	dy;
	int		i;

	dx = game->pdx;
	dy = game->pdy;
	i = 5;
	while (i-- > 0)
	{
		dx += dx;
		dy += dy;
		mlx_pixel_put(game->mlx, game->win, game->player_x + dx, \
			game->player_y + dy, 0x0000FF);
	}
}

void	move_player_1px(t_game *game, int steps, float dx, float dy)
{
	// if ((game->player_y + dy) >= WIN_HEIGHT || (game->player_x + dx) >= WIN_WIDTH || \
	// 	(game->player_y + dy) < 0 || (game->player_x + dx) < 0)
	// 	return ;
    while (steps-- > 0)
    {
        if ((game->player_y + dy) >= WIN_HEIGHT || (game->player_x + dx) >= WIN_WIDTH || \
			(game->player_y + dy) < 0 || (game->player_x + dx) < 0)
			return ;
		if (game->map[(int)((game->player_y) / TILE_SIZE)][(int)((game->player_x) / TILE_SIZE)] == '1')
			mlx_pixel_put(game->mlx, game->win, game->player_x, game->player_y, 0xFF0000);
		else
			mlx_pixel_put(game->mlx, game->win, game->player_x, game->player_y, 0xAAAAAA);
		mlx_pixel_put(game->mlx, game->win, game->player_x + dx, \
                game->player_y + dy, 0xFFFF00);
        game->player_x += dx;
        game->player_y += dy;
    }
	draw_ray_5px(game);
}

void	get_end_of_vector(float px, float py, double angle)
{
	float	lx;
	float	ly;
	float	lz;
	float	new_px;
	float	new_py;

	printf("---------------------------------------------------------\n");
	printf("px = %f\npy = %f\nangle = %f\n", px,py,angle);
	if (angle >= 0 && angle <= 0.5*PI)
	{
		lx = (((int)(px / TILE_SIZE) + 1) * TILE_SIZE) - px;
		// lx = (TILE_SIZE) - px;
		ly = lx * tanf(angle);
		lz = lx / cosf(angle);
		new_px = px + lx;
		new_py = py - ly;
	}
	else if (angle > 90 && angle <= PI)
	{
		angle = PI - angle;
		lx = px;
		ly = lx * tanf(angle);
		lz = lx / cosf(angle);
		new_px = px - lx;
		new_py = py - ly;
	}
	else if (angle > 180 && angle <= 1.5*PI)
	{
		angle = angle - PI;
		lx = px;
		ly = lx * tanf(angle);
		lz = lx / cosf(angle);
		new_px = px - lx;
		new_py = py + ly;
	}
	else
	{
		angle = 2*PI - angle;
		lx = TILE_SIZE - px;
		ly = lx * tanf(angle);
		lz = lx / cosf(angle);
		new_px = px + lx;
		new_py = py + ly;
	}
	printf("lx = %f\nly = %f\nlz = %f\nnew_px = %f\nnew_py = %f\n", lx,ly,lz,new_px,new_py);
	printf("---------------------------------------------------------\n");
}

float	change_angle(float angle, float change, int flag) // 0 angle change only, 1 dx change , 2 dy change
{
	float	new_angle;

	new_angle = angle + change;
	if (new_angle >= 360)
		new_angle -= 360;
	else if (new_angle <= 0)
		new_angle += 360;
	if (flag == 0)
		return (new_angle);
	if (flag == 1)
		return (cosf(new_angle * (PI/180)));
	if (flag == 2)
		return (sinf(new_angle * (PI/180)));
	write(1, "change_angle invalid flag\n", 26);
	return (new_angle); // just return new angle if flag is incorrect
}
