/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:51:27 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/19 21:27:20 by cafriem          ###   ########.fr       */
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

void	draw_line(t_game *game, t_point end, int location, int color)
{
	float	line_length;
	int	line_location;

	(void)color;
	// line_length = end.length;
	if (end.length < 5.0f)
		line_length = WIN_HEIGHT;
	else
	{
		line_length = ((320*TILE_SIZE) / end.length); // * cosf((game->angle - end.angle) * PI/180);
		printf("line_length = %f\n",line_length);
	}
	// line_length = line_length * cos(game->angle + (location - 30));
	if (line_length > WIN_HEIGHT)
		line_length = WIN_HEIGHT;
	line_location = -line_length + (line_length/2);
	// printf("length     = %d\n", line_length);
	while (line_length-- > 0)
	{
		if (end.face == 'N')
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0xec8df8);
		else if (end.face == 'S')
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0x62106d);
		else if (end.face == 'E')
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0xda20f1);
		else if (end.face == 'W')
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0x69516c);
		else
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0x000000);
		// printf("line_length = %d           line_location = %d\n", line_length, line_location);
	}
}

void	rendering_3d(t_game *game)
{
	int		i;
	int		x;
	t_point	end;
	float	angle;
	float	dif;
	
	i = 0;
	x = 0;
	angle = game->angle + 30.0f;
	dif = 60.0f / WIN_WIDTH;
	while (i < WIN_WIDTH)
	{
		printf("=========================== %f - %f       ray %d\n", angle, dif, i);
		end = raycast_custom_angle(game, angle);
		end.ray_num = i;
		draw_line(game, end, x++, 0x090c66);
		if ((angle - dif) < 0.000001)
			angle = 360;
		angle = angle - dif;
		i++;
	}
}

void	draw_3d(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
								&game->img.endian);
	draw_background_3d(game, 0x84c8d1, 0x1f5c2c);
	rendering_3d(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
