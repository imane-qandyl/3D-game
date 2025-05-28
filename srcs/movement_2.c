/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:54:17 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/26 02:59:00 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_pressed(int key, t_game *game)
{
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

int	key_release(int key, t_game *game)
{
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

double	change_angle(double angle, double change, int flag)
{
	double	new_angle;

	new_angle = angle + change;
	if (new_angle >= 360)
		new_angle -= 360;
	else if (new_angle <= 0)
		new_angle += 360;
	if (flag == 0)
		return (new_angle);
	if (flag == 1)
		return (cos(new_angle * (PI / 180)));
	if (flag == 2)
		return (sin(new_angle * (PI / 180)));
	write(1, "change_angle invalid flag\n", 26);
	return (new_angle);
}
