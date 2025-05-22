/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:51:27 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/22 16:34:36 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_background_3d(t_game *game, int sky, int floor)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y < (WIN_HEIGHT/2))
				my_mlx_pixel_put(&game->img, x, y, sky);
			else
				my_mlx_pixel_put(&game->img, x, y, floor);
		}
	}
}

void	init_point(t_point *point)
{
	point->angle = 0.0;
	point->dx = 0.0;
	point->dy = 0.0;
	point->face = '0';
	point->length = 0.0;
	point->ray_num = 0;
	point->x = 0.0;
	point->y = 0.0;
}

void	draw_wall_line(t_game *game, t_point end, int location)
{
	double	line_height;
	int		line_location;
	int		texture_x;
	double		texture_y;
	double	text_increment_y;
	int color;
	
	if(end.length < 5.0f)
		line_height = WIN_WIDTH;
	else
		line_height = ((WIN_WIDTH*TILE_SIZE)/end.length);
	if (line_height > WIN_WIDTH)
		line_height = WIN_WIDTH;
	line_location = -line_height + (line_height/2);
	// printf("line_height = %f\n", line_height
	if (end.face == 'N' || end.face == 'S')
		texture_x = (int)end.x % TILE_SIZE;
	else
		texture_x = (int)end.y % TILE_SIZE;
	if (line_height == WIN_WIDTH)
	{
		texture_y = ((((WIN_WIDTH*TILE_SIZE)/end.length)) - WIN_HEIGHT) / 2;
		texture_y = 64/ texture_y;
	}
	else
		texture_y = 0;
	text_increment_y = game->tex_height / ((WIN_WIDTH*TILE_SIZE)/end.length);
	// printf("face = %c\n", end.face);
	// printf("texture\n x = %d\ny = %f\nincrement = %f\n\n", texture_x, texture_y, text_increment_y);
	while (line_height-- > 0)
	{
		color = game->texture_map_test[(int)(texture_y)][texture_x];
		my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 
							color);
		texture_y += text_increment_y;
	}
	// printf("x = %d\ny = %f\nincrement = %f\ncolor = %d\n\n\n", texture_x, texture_y, text_increment_y, color);
}

void	rendering_3d(t_game *game)
{
	double	ray_angle; // angle of the ray 
	double	next_ray;  // increment to the next ray
	int		i;         // the x point on the window
	t_point	end_point; // the point where the ray lands

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
								
	draw_background_3d(game, 0x84c8d1, 0x1f5c2c);
	rendering_3d(game);
	
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
