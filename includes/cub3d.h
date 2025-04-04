/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:19:31 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/04 11:23:26 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../includes/mlx.h"

# define TILE_SIZE 32
# define WIN_WIDTH 640
# define WIN_HEIGHT 480

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
}	t_game;

char	**read_map(const char *filename);
void	draw_map(t_game *game);
void	free_map(char **map);

#endif
