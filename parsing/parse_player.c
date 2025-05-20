/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:12 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/03 13:09:10 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
char get_player_direction(t_game *game) {
    int i, j;
    i= 0;
    while(i < game->map_height) {
        j = 0;
        while(j < game->map_width) {
            char c = game->map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
                return c;
            }
            j++;
        }
        i++;
    }
    // Default direction if not found
    return 'N';
}

void get_player_position(t_game *game) {
    int i, j;
    i = 0;
   while(i < game->map_height) {
        j = 0;
        while (j < game->map_width) {
            char c = game->map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
                game->p.px = j * TILE_SIZE + (TILE_SIZE / 2);
                game->p.py = i * TILE_SIZE + (TILE_SIZE / 2);
                printf("player position: %f, %f\n", game->p.px, game->p.py);
                return;
            }
            j++;
        }
        i++;
    }
}