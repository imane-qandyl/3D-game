/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:26:04 by lalwafi           #+#    #+#             */
/*   Updated: 2025/04/26 17:32:10 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int key_pressed(int key, t_game *game)
{
	write(1, "key press\n", 4);
	if (key == ESC)
		return (finish(game, 0));
	if (key == W)
		game->key.w = true;
	if (key == A)
		game->key.a = true;
	if (key == S)
		game->key.s = true;
	if (key == D)
		game->key.d = true;
	if (key == LEFT)
		game->key.left = true;
	if (key == RIGHT)
		game->key.right = true;
	return (0);
}

int key_release(int key, t_game *game)
{
	write(1, "key release\n", 4);
	if (key == W)
		game->key.w = false;
	if (key == A)
		game->key.a = false;
	if (key == S)
		game->key.s = false;
	if (key == D)
		game->key.d = false;
	if (key == LEFT)
		game->key.left = false;
	if (key == RIGHT)
		game->key.right = false;
	return (0);
}

int	movement(t_game *game)
{
	if (game->key.w == true)
	{
		move_player_1px(game, 1, game->pdx, game->pdy);
		print_everything_for_debug(game);
		draw_map(game);
		draw_player(game);
	}
	if (game->key.a == true)
	{
		move_player_1px(game, 1, change_angle(game->angle, 270, 1), change_angle(game->angle, 270, 2));
		print_everything_for_debug(game);
		draw_map(game);
		draw_player(game);
	}
	if (game->key.s == true)
	{
		move_player_1px(game, 1, change_angle(game->angle, 180, 1), change_angle(game->angle, 180, 2));
		print_everything_for_debug(game);
		draw_map(game);
		draw_player(game);
	}
	if (game->key.d == true)
	{
		move_player_1px(game, 1, change_angle(game->angle, 90, 1), change_angle(game->angle, 90, 2));
		print_everything_for_debug(game);
		draw_map(game);
		draw_player(game);
	}
	if (game->key.left == true)
	{
		game->angle -= 1;
		if (game->angle < 0)
			game->angle += 360;
		game->pdx = cosf(game->angle * PI/180);
		game->pdy = sinf(game->angle * PI/180);
		print_everything_for_debug(game);
		draw_map(game);
		draw_player(game);
	}
	if (game->key.right == true)
	{
		game->angle += 1;
		if (game->angle >= 360)
			game->angle -= 360;
		game->pdx = cosf(game->angle * PI/180);
		game->pdy = sinf(game->angle * PI/180);
		print_everything_for_debug(game);
		draw_map(game);
		draw_player(game);
	}
	return (0);
}

void	move_player_1px(t_game *game, int steps, float dx, float dy)
{
	while (steps-- > 0)
	{
		if ((game->p.py + dy) >= WIN_HEIGHT || (game->p.px + dx) >= WIN_WIDTH || \
			(game->p.py + dy) < 0 || (game->p.px + dx) < 0 || \
			game->map[(int)((game->p.py + dy)/TILE_SIZE)][(int)((game->p.px + dx)/TILE_SIZE)] == '1')
			return ;
		game->p.px += dx;
		game->p.py += dy;
	}
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
	printf("angle   = %f\n", game->angle);
	printf("x       = %f\n", game->p.px);
	printf("y       = %f\n", game->p.py);
	printf("dx      = %f\n", game->pdx);
	printf("dy      = %f\n", game->pdy);
	printf("tile y  = %d\n", (int)(game->p.py/TILE_SIZE));
	printf("tile x  = %d\n", (int)(game->p.px/TILE_SIZE));
	printf("--------------------------\n");
}
