/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:26:04 by lalwafi           #+#    #+#             */
/*   Updated: 2025/04/09 21:55:39 by lalwafi          ###   ########.fr       */
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
		;
	if (key == RIGHT)	
		;
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
			// check if floor or wall, ill put floor for now
			printf("1 : %d\n", ((game->player_x + x) / TILE_SIZE));
			if (game->map[((game->player_y + y) / TILE_SIZE)][((game->player_x + x) / TILE_SIZE)] == '1')
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

