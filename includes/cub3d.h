/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:19:31 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/10 19:53:05 by lalwafi          ###   ########.fr       */
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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_data	img;
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		tex_width;
	int		tex_height;
	int		floor_color[3];
	int		ceiling_color[3];
	int		map_width;
	int		map_height;
	char	player_dir;
	float	player_x;
	float	player_y;
	float	angle;
	float	pdx;
	float	pdy;
}	t_game;

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
void	move_player(t_game *game, float dx, float dy);
void	move_player_1px(t_game *game, int steps, float dx, float dy);
void	move_player_2px(t_game *game, int steps, float dx, float dy);
int		finish(t_game *game, int i);
// void	get_end_of_vector(float px, float py, double angle);
float	change_angle(float angle, float change, int flag);
void	draw_ray_5px(t_game *game);
float	length_of_raycast_H(t_game *game, float px, float py, double angle);


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
