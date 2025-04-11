/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:19:31 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/11 07:18:59 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include "../includes/mlx.h"

# define TILE_SIZE 32
# define WIN_WIDTH 1100
# define WIN_HEIGHT 500
# define PI 3.141592653589
typedef enum e_error {
    ERR_NONE,
    ERR_MALLOC,
    ERR_INVALID_FILE,
    ERR_MISSING_TEXTURE,
    ERR_INVALID_COLOR,
    ERR_INVALID_MAP,
    ERR_PLAYER_COUNT,
    ERR_MAP_NOT_CLOSED
} t_error;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
    int     tex_width;
    int     tex_height;
    int     floor_color[3];
    int     ceiling_color[3];
    int     map_width;
    int     map_height;
    char    player_dir;
    int     player_x;
    int     player_y;
	float	player_dx;
	float	player_dy;
}	t_game;

/* Function prototypes */
// Initialization and cleanup
void    init_map_info(t_game *info);
void    free_map_info(t_game *info);

// Parsing functions
t_error parse_file(const char *filename, t_game *info);
t_error parse_textures(char *line, t_game *info);
t_error parse_colors(char *line, t_game *info);
t_error parse_map_content(char **lines, t_game *info);
t_error validate_map(t_game *info);
void    print_error(t_error error);

// Map functions
char    **read_map(const char *filename);
void    print_map(char **map);
void    free_map(char **map);


typedef enum keys
{
	W = 13,
	A= 0,
	S = 1,
	D = 2,
	ESC = 53,
	UP = 126,
	DOWN = 125,
	RIGHT = 124,
	LEFT = 123
}	t_keys;

char	**read_map(const char *filename);
void	draw_map(t_game *game);
void	free_map(char **map);
void	draw_player(t_game *game);
int		key_pressed(int key, t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
int		finish(t_game *game, int i);
void	get_end_of_vector(float px, float py, double angle);

#endif
