/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:12 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/24 17:54:48 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	get_player_direction(t_game *game)
{
	char	c;
	int		j;
	int		i;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			c = game->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				return (c);
			}
			j++;
		}
		i++;
	}
	return ('N');
}

void	get_player_position(t_game *game)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			c = game->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->p.x = j * TILE_SIZE + (TILE_SIZE / 2);
				game->p.y = i * TILE_SIZE + (TILE_SIZE / 2);
				printf("player position: %f, %f\n", game->p.x, game->p.y);
				return ;
			}
			j++;
		}
		i++;
	}
}
