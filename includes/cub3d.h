/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:19:31 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/26 17:30:25 by lalwafi          ###   ########.fr       */
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
# include <stdbool.h>

# define TILE_SIZE 32
# define WIN_WIDTH 1100
# define WIN_HEIGHT 500
# define PI 3.141592653589

# ifdef OSX
#  include "../includes/mlx.h"
#  include <mlx.h>
#  define ESC 53
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define LEFT 123
#  define RIGHT 124
# else
#  include "../mlx-linux/mlx.h"
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define LEFT 65361
#  define RIGHT 65363
# endif

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

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
} t_keys;

typedef struct s_point
{
	float	px;
	float	py;
	float	length;
} t_point;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_data		img;
	char		**map;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			tex_width;
	int			tex_height;
	int			floor_color[3];
	int			ceiling_color[3];
	int			map_width;
	int			map_height;
	char		player_dir;
	t_point		p;       // player coordinates
	t_keys		key;
	float		angle;
	float		pdx;
	float		pdy;
}	t_game;



char		**read_map(const char *filename);
void		draw_map(t_game *game);
void		free_map(char **map);
void		draw_player(t_game *game);
int			key_pressed(int key, t_game *game);
int 		key_release(int key, t_game *game);
int			movement(t_game *game);
void		move_player_1px(t_game *game, int steps, float dx, float dy);
int			finish(t_game *game, int i);
// void		get_end_of_vector(float px, float py, double angle);
float		change_angle(float angle, float change, int flag);
void		draw_ray_5px(t_game *game);
t_point		length_of_raycast_H(t_game *game);
float		length_of_raycast_V(t_game *game, float px, float py, int angle);
t_point 	horizontal_raycast(t_game *game);
t_point 	vertical_raycast(t_game *game);
t_point		which_ray_shorter(t_game *game, t_point ph, t_point pv);
void		draw_ray(t_game *game, t_point point);
void		dda_thing(t_game *game);
void		dda(t_game *game, t_point end, int color);


void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		print_everything_for_debug(t_game *game);

#endif
