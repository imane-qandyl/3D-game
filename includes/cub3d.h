/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:19:31 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/08 15:35:36 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
#include <ctype.h>
# include <math.h>
# include <stdbool.h>
#include <fcntl.h>     // for open()
#include <unistd.h>    // for close()
# include "../includes/mlx.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

# define TILE_SIZE 32
# define WIN_WIDTH 960
# define WIN_HEIGHT 480
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
	ERR_MAP_NOT_CLOSED,
	ERR_DUPLICATE_TEXTURE,
    ERR_DUPLICATE_COLOR,
	ERR_DUPLICATE_PLAYER,
	ERR_NO_PLAYER
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

/* Function prototypes */
// Initialization and cleanup
void    init_map_info(t_game *info);
void    free_map_info(t_game *info);

// Parsing functions
t_error parse_file(const char *filename, t_game *info);
t_error	parse_textures(char *line, t_game *info);
t_error parse_colors(char *line, t_game *info);
t_error parse_map_content(char **lines, t_game *info);
int	validate_texture_file(const char *path);
char	*extract_path(const char *line);
int	is_valid_color(int value);
t_error	parse_color_value(const char *str, int *color);
t_error check_player_count(char **map);
char get_player_direction(t_game *game);
void get_player_position(t_game *game);

// t_error validate_map(char **map_lines, t_game *info);
t_error validate_map(t_game *info);
// char	*ft_strchr(const char *s, int c);
// int     is_map_line(char *line);
int	is_empty_line(const char *line);
int	is_map_line(char *line);

void    print_error(t_error error);
int get_map_width(char **lines);
int count_map_lines(char **lines);
char *skip_spaces(char *line);
void free_lines(char **lines);
char **read_all_lines(int fd);

// Map functions
char **read_map(char **lines);
void    free_map(char **map);
void pad_map_lines(char **map, int height, int width);

// Execution functions
void    	draw_2d(t_game *game);
void    	free_map(char **map);
void    	draw_player(t_game *game);
int			key_pressed(int key, t_game *game);
int 		key_release(int key, t_game *game);
int			movement(t_game *game);
void		move_player_1px(t_game *game, int steps, float dx, float dy);
int			finish(t_game *game, int i);
float		change_angle(float angle, float change, int flag);
void		draw_ray_5px(t_game *game);
t_point		which_ray_shorter(t_game *game, t_point ph, t_point pv);
void		draw_ray(t_game *game, t_point point, int color);
void		draw_ray_custom_angle(t_game *game, t_point point, int angle, int color);
t_point		just_raycast(t_game *game);
t_point		just_raycast_custom_angle(t_game *game, int angle);
void		dda_thing(t_game *game);
// void		dda(t_game *game, t_point end, int color);
void		draw_background(t_game *game, int sky, int floor);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		print_everything_for_debug(t_game *game);
void	draw_line(t_game *game, t_point end, int location, int color);
void	dda_only_3d(t_game *game);
void	draw_3d(t_game *game);

#endif
