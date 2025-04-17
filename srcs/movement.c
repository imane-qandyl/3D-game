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

	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
								&game->img.endian);
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
	if (key == LEFT)
	{
		game->angle -= 5;
		if (game->angle >= 360)
			game->angle -= 360;
		game->pdx = cosf(game->angle * PI/180);
		game->pdy = sinf(game->angle * PI/180);
		// get_end_of_vector(game->player_x, game->player_y, game->angle * (PI/180));
		draw_ray_5px(game);
		// length_of_raycast_H(game, game->player_x, game->player_y, (game->angle * PI/180));
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
		// length_of_raycast_H(game, game->player_x, game->player_y, (game->angle * PI/180));
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_destroy_image(&game->mlx, &game->img);
	return (0);
}

void	draw_ray_5px(t_game *game)
{
	float	dx;
	float	dy;
	int		i;

	dx = game->pdx;
	dy = game->pdy;
	
	i = 10;
	while (i-- > 0)
	{
		my_mlx_pixel_put(&game->img, game->player_x + dx, \
			game->player_y + dy, 0x0000FF);
		dx += game->pdx;
		dy += game->pdy;
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
		my_mlx_pixel_put(&game->img, game->player_x + dx, \
                game->player_y + dy, 0xFFFF00);
        game->player_x += dx;
        game->player_y += dy;
    }
	draw_ray_5px(game);
}

float	length_of_raycast_H(t_game *game, float px, float py, double angle) // increment Y 
{
	float	lz;
	int		i;

	if (angle == 0 || angle == PI)
		return (-1);
	lz = 0;
	if (angle > 0 && angle < PI)
	{
		i = (int)py;
		while (game->map[(int)py][(int)px] != '1' && (py - i) > 0)
		{
			lz = (py - i)/sinf(angle);
			i--;
		}
	}
	else if (angle > PI && angle <= (2*PI))
	{
		i = (int)py + 1;
		while (game->map[(int)py][(int)px] != '1' && i < WIN_WIDTH)
		{
			lz = (i - py)/sinf(angle);
			i++;
		}
	}
	printf("lz horizontal = %f\n", lz);
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
