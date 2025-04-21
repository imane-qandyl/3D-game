/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:26:04 by lalwafi           #+#    #+#             */
/*   Updated: 2025/04/21 04:03:45 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int key_pressed(int key, t_game *game)
{
	write(1, "key\n", 4);
	draw_map(game);
	draw_player(game);
	if (key == ESC)
		finish(game, 0);
	if (key == W)
		move_player_1px(game, 1, game->pdx, game->pdy);
	if (key == A)
		move_player_1px(game, 1, change_angle(game->angle, 270, 1), change_angle(game->angle, 270, 2));
	if (key == S)
		move_player_1px(game, 1, change_angle(game->angle, 180, 1), change_angle(game->angle, 180, 2));
	if (key == D)
	move_player_1px(game, 1, change_angle(game->angle, 90, 1), change_angle(game->angle, 90, 2));
	if (key == RIGHT)	
	{
		printf("left\n");
		game->angle += 5;
		if (game->angle >= 360)
		game->angle -= 360;
		game->pdx = cosf(game->angle * PI/180);
		game->pdy = sinf(game->angle * PI/180);
		// get_end_of_vector(game->player_x, game->player_y, game->angle * (PI/180));
		// length_of_raycast_H(game, game->player_x, game->player_y, (game->angle * PI/180));
	}
	if (key == LEFT)
	{
		printf("right\n");
		game->angle -= 5;
		if (game->angle < 0)
			game->angle += 360;	
		game->pdx = cosf(game->angle * PI/180);
		game->pdy = sinf(game->angle * PI/180);
		// get_end_of_vector(game->player_x, game->player_y, game->angle * (PI/180));
		// length_of_raycast_H(game, game->player_x, game->player_y, (game->angle * PI/180));
	}
	print_everything_for_debug(game);
	length_of_raycast_H(game, (game->player_x/TILE_SIZE), (game->player_y/TILE_SIZE), (game->angle * (PI/180)));
	length_of_raycast_V(game, (game->player_x/TILE_SIZE), (game->player_y/TILE_SIZE), (game->angle * (PI/180)));
	// mlx_destroy_image(&game->mlx, &game->img);
	return (0);
}

void	move_player_1px(t_game *game, int steps, float dx, float dy)
{
    while (steps-- > 0)
    {
        if ((game->player_y + dy) >= WIN_HEIGHT || (game->player_x + dx) >= WIN_WIDTH || \
			(game->player_y + dy) < 0 || (game->player_x + dx) < 0)
			return ;
		my_mlx_pixel_put(&game->img, game->player_x + dx, \
                game->player_y + dy, 0xFFFF00);
        game->player_x += dx;
        game->player_y += dy;
    }
}

void	move_player_2px(t_game *game, int steps, float dx, float dy)
{
	int	x;
	int	y;
	
	x = -1;
	y = -1;
	(void)steps;
	while (++y < 4)
	{
		while (++x < 4)
		{
			if (game->map[(int)((game->player_y + y) / TILE_SIZE)][(int)((game->player_x + x) / TILE_SIZE)] == '1')
				mlx_pixel_put(game->mlx, game->win, game->player_x + x, game->player_y + y, 0xFF0000);
			else
				mlx_pixel_put(game->mlx, game->win, game->player_x + x, game->player_y + y, 0xAAAAAA);
			mlx_pixel_put(game->mlx, game->win,\
						game->player_x + x + dx,\
						game->player_y + y + dy, 0xFFFF00);
		}
		x = -1;
	}
	game->player_x += dx;
	game->player_y += dy;
}

float	length_of_raycast_H(t_game *game, float px, float py, double angle) // increment Y 
{
	float	lz;
	int		i;

	if (angle == 0 || angle == PI || angle == 2*PI)
		return (-1);
	lz = 0;
	printf("------------------------lz H\nlz horizontal = %f\npx = %f\npy = %f\nangle = %f\n\n", lz, px, py, angle);
	if (angle > PI && angle <= (2*PI))
	{
		i = (int)py;
		while (i >= 0 && px >= 0 && game->map[i][(int)px] != '1')
		{
			printf("inside 0-PI   i = %d\n", i);
			lz += (py - i)/sinf(angle);
			i--;
		}
	}
	else if (angle > 0 && angle < PI)
	{
		i = (int)py + 1;
		while (i <= (WIN_HEIGHT/TILE_SIZE) && px <= (WIN_WIDTH/TILE_SIZE) && game->map[i][(int)px] != '1')
		{
			printf("inside PI-2PI   i = %d\n", i);
			lz += (i - py)/sinf(angle);
			i++;
		}
	}
	printf("lz horizontal = %f\npx = %f\npy = %f\nangle = %f\n------------------------\n", lz, px, py, angle);
	return (lz);
}

float	length_of_raycast_V(t_game *game, float px, float py, double angle) // increment x 
{
	float	lz;
	int		i;

	if (angle == (PI*1.5) || angle == (PI/2))
		return (-1);
	lz = 0;
	printf("------------------------lz V\nlz vertical = %f\npx = %f\npy = %f\nangle = %f\n\n", lz, px, py, angle);
	if (angle > (PI/2) && angle < (PI*1.5))
	{
		i = (int)px;
		while (i >= 0 && py >= 0 && game->map[(int)py][i] != '1')
		{
			printf("inside PI/2-PI*1.5   i = %d\n", i);
			lz += (px - i)/cosf(angle);
			i--;
		}
	}
	else if (angle > (PI*1.5) || angle < (PI/2))
	{
		i = (int)px + 1;
		printf("here??n");
		while (i <= (WIN_WIDTH/TILE_SIZE) && py <= (WIN_HEIGHT/TILE_SIZE) && game->map[(int)py][i] != '1')
		{
			printf("inside PI*1.5-PI/2   i = %d\n", i);
			lz += (i - px)/cosf(angle);
			i++;
		}
	}
	printf("lz vertical = %f\npx = %f\npy = %f\nangle = %f\n------------------------\n", lz, px, py, angle);
	return (lz);
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

void	print_everything_for_debug(t_game *game)
{
	printf("--------------------------\n");
	printf("angle = %f\n", game->angle);
	printf("x     = %f\n", game->player_x);
	printf("y     = %f\n", game->player_y);
	printf("dx    = %f\n", game->pdx);
	printf("dy    = %f\n", game->pdy);
	printf("--------------------------\n");
}
