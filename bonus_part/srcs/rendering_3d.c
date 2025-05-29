/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:51:27 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/29 21:15:38 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

static void	draw_wall_line_2(t_game *game, t_draw draw, t_point end, int x)
{
	while (draw.line_height-- > 0)
	{
		if (end.face == 'N')
			my_mlx_pixel_put(&game->img, x,
				(WIN_HEIGHT / 2) + draw.line_location++,
				game->no_tex_map[(int)(draw.texture_y)][draw.texture_x]);
		else if (end.face == 'S')
			my_mlx_pixel_put(&game->img, x,
				(WIN_HEIGHT / 2) + draw.line_location++,
				game->so_tex_map[(int)(draw.texture_y)][draw.texture_x]);
		else if (end.face == 'E')
			my_mlx_pixel_put(&game->img, x,
				(WIN_HEIGHT / 2) + draw.line_location++,
				game->ea_tex_map[(int)(draw.texture_y)][draw.texture_x]);
		else if (end.face == 'W')
			my_mlx_pixel_put(&game->img, x,
				(WIN_HEIGHT / 2) + draw.line_location++,
				game->we_tex_map[(int)(draw.texture_y)][draw.texture_x]);
		draw.texture_y += draw.text_increment_y;
	}
}

void	draw_wall_line(t_game *game, t_point end, int x)
{
	t_draw	draw;
	double	real_line_height;

	draw.line_height = ((WIN_WIDTH * TILE_SIZE) / end.length);
	real_line_height = draw.line_height;
	if (draw.line_height > WIN_HEIGHT)
		draw.line_height = WIN_HEIGHT;
	draw.line_location = -draw.line_height + (draw.line_height / 2);
	if (end.face == 'N' || end.face == 'S')
		draw.texture_x = (int)end.x % TILE_SIZE;
	else
		draw.texture_x = (int)end.y % TILE_SIZE;
	if (draw.line_height == WIN_WIDTH)
	{
		draw.texture_y = ((((WIN_WIDTH * TILE_SIZE) / end.length))
				- WIN_HEIGHT) / 2;
		draw.texture_y = 64 / draw.texture_y;
	}
	else
		draw.texture_y = 0;
	draw.text_increment_y = game->tex_height
		/ ((WIN_WIDTH * TILE_SIZE) / end.length);
	draw.texture_y += draw.text_increment_y
		* ((real_line_height - draw.line_height) / 2);
	draw_wall_line_2(game, draw, end, x);
}

void	rendering_3d(t_game *game)
{
	double	ray_angle;
	double	next_ray;
	int		i;
	t_point	end_point;

	i = WIN_WIDTH;
	ray_angle = game->angle + 30;
	next_ray = 60.0 / WIN_WIDTH;
	init_point(&end_point);
	while (--i >= 0)
	{
		end_point.ray_num = i;
		end_point = raycast_v_h(game, ray_angle);
		draw_wall_line(game, end_point, i);
		ray_angle -= next_ray;
		if (ray_angle < 0)
			ray_angle += 360;
	}
}

void	draw_3d(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	draw_background_3d(game,
		rgb_to_hex(game->ceiling_color[0],
			game->ceiling_color[1], game->ceiling_color[2]),
		rgb_to_hex(game->floor_color[0],
			game->floor_color[1], game->floor_color[2]));
	rendering_3d(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
