/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:19:31 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/29 22:16:21 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include "../includes/mlx.h"
# include "../libft/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <fcntl.h> // for open()
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <unistd.h> // for close()

# define TILE_SIZE 64
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
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

typedef enum e_error
{
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
}			t_error;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
}			t_keys;

typedef struct s_point
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	length;
	char	face; // N,S,E,W
	double	angle;
	int		ray_num; // number of the ray
}			t_point;

typedef struct s_draw
{
	double	line_height;
	int		line_location;
	int		texture_x;
	double	texture_y;
	double	text_increment_y;
}			t_draw;

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
	int		no_tex_map[64][64];
	int		so_tex_map[64][64];
	int		ea_tex_map[64][64];
	int		we_tex_map[64][64];
	int		tex_width;
	int		tex_height;
	int		floor_color[3];
	int		ceiling_color[3];
	int		map_width;
	int		map_height;
	char	player_dir;
	t_point	p;
	t_keys	key;
	double	angle;
	double	dx;
	double	dy;
}			t_game;

void		init_map_info(t_game *info);
void		free_map_info(t_game *info);

// Parsing functions
t_error		parse_file(const char *filename, t_game *info);
int			load_textures(t_game *game);
t_error		parse_textures(char *line, t_game *info);
t_error		parse_colors(char *line, t_game *info);
int			is_valid_color(int value);
t_error		parse_color_value(const char *str, int *color);
t_error		validate_color_range(int *target);

t_error		parse_map_content(char **lines, t_game *info);
int			validate_texture_file(const char *path);
char		*extract_path(const char *line);

t_error		check_player_count(char **map);
char		get_player_direction(t_game *game);
void		get_player_position(t_game *game);

// t_error validate_map(char **map_lines, t_game *info);
t_error		validate_map(t_game *info);
// char	*ft_strchr(const char *s, int c);
// int     is_map_line(char *line);
int			is_empty_line(const char *line);
int			is_map_line(char *line);

// New helper functions
int			is_map_start(char *line);
int			is_config_line(char *line);
int			is_map_start_line(char *line);

t_error		validate_horizontal_edges(char **map, int width, int height);
t_error		validate_vertical_edges(char **map, int width, int height);
t_error		validate_holes(char **map, int width, int height);

void		print_error(t_error error);
int			get_map_width(char **lines);
int			count_map_lines(char **lines);
void		strip_newline(char *line);
char		*skip_spaces(char *line);
void		free_lines(char **lines);
char		**read_all_lines(int fd);

// Map functions
char		**read_map(char **lines);
void		free_map(char **map);
void		pad_map_lines(char **map, int height, int width);

// Execution functions
void		exec_init(t_game *game);
void		make_texture_maps(t_game *game);
int			get_angle(char c);
void		draw_2d(t_game *game);
void		free_map(char **map);
void		draw_player(t_game *game);
int			key_pressed(int key, t_game *game);
int			key_release(int key, t_game *game);
int			movement(t_game *game);
int			finish(t_game *game, int i);
void		rendering_2d(t_game *game);
void		draw_background_3d(t_game *game, int ceiling, int floor);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		rendering_3d(t_game *game);
void		draw_3d(t_game *game);

// try 2
int			movement(t_game *game);
void		move_player(t_game *game, double dx, double dy);
void		rotate_player(t_game *game, int angle_change);
int			key_pressed(int key, t_game *game);
int			key_release(int key, t_game *game);
double		change_angle(double angle, double change, int flag);
t_point		round_endpoint(t_point ph, int angle);
t_point		raycast(t_game *game, double ray_angle);
void		rendering_2d(t_game *game);
void		dda(t_game *game, t_point end);
void		draw_background_3d(t_game *game, int ceiling, int floor);
void		init_point(t_point *point);
void		rendering_3d(t_game *game);
void		draw_3d(t_game *game);

t_point		raycast_horizontal(t_game *game, double ray_angle);
t_point		raycast_vertical(t_game *game, double ray_angle);
t_point		raycast_v_h(t_game *game, double ray_angle);
void		draw_wall_line(t_game *game, t_point end, int x);
int			rgb_to_hex(int red, int green, int blue);

#endif
