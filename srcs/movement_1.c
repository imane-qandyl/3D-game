/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:32:23 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/29 17:35:07 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	moving_or_not(t_game *game)
{
	if (game->key.w == true
		|| game->key.a == true
		|| game->key.s == true
		|| game->key.d == true
		|| game->key.right == true
		|| game->key.left == true)
		return (true);
	return (false);
}

int	movement(t_game *game)
{
	if (game->key.w == true)
		move_player(game, game->dx, game->dy);
	if (game->key.a == true)
		move_player(game, change_angle(game->angle, 270, 1),
			change_angle(game->angle, 270, 2));
	if (game->key.s == true)
		move_player(game, change_angle(game->angle, 180, 1),
			change_angle(game->angle, 180, 2));
	if (game->key.d == true)
		move_player(game, change_angle(game->angle, 90, 1),
			change_angle(game->angle, 90, 2));
	if (game->key.right == true)
		rotate_player(game, +3);
	if (game->key.left == true)
		rotate_player(game, -3);
	if (moving_or_not(game) == true)
		draw_3d(game);
	return (0);
}

void	move_player(t_game *game, double dx, double dy)
{
	if (game->map[(int)((game->p.y + (dy * 5) + 10) / TILE_SIZE)]
		[(int)((game->p.x + (dx * 5)) / TILE_SIZE)] != '1' &&
		game->map[(int)((game->p.y + (dy * 5) - 10) / TILE_SIZE)]
			[(int)((game->p.x + (dx * 5)) / TILE_SIZE)] != '1' &&
		game->map[(int)((game->p.y + (dy * 5)) / TILE_SIZE)]
			[(int)((game->p.x + (dx * 5) + 10) / TILE_SIZE)] != '1' &&
		game->map[(int)((game->p.y + (dy * 5)) / TILE_SIZE)]
			[(int)((game->p.x + (dx * 5) - 10) / TILE_SIZE)] != '1' &&
		game->map[(int)((game->p.y + (dy * 5) + 10) / TILE_SIZE)]
			[(int)((game->p.x + (dx * 5) + 10) / TILE_SIZE)] != '1' &&
		game->map[(int)((game->p.y + (dy * 5) - 10) / TILE_SIZE)]
			[(int)((game->p.x + (dx * 5) - 10) / TILE_SIZE)] != '1' &&
			game->map[(int)((game->p.y + (dy * 5) + 10) / TILE_SIZE)]
				[(int)((game->p.x + (dx * 5) - 10) / TILE_SIZE)] != '1' &&
			game->map[(int)((game->p.y + (dy * 5) - 10) / TILE_SIZE)]
				[(int)((game->p.x + (dx * 5) + 10) / TILE_SIZE)] != '1')
	{
		game->p.x += (dx * 5);
		game->p.y += (dy * 5);
	}
}

void	rotate_player(t_game *game, int angle_change)
{
	game->angle += angle_change;
	if (game->angle < 0)
		game->angle += 360;
	if (game->angle >= 360)
		game->angle -= 360;
	game->dx = cos(game->angle * PI / 180);
	game->dy = sin(game->angle * PI / 180);
}
