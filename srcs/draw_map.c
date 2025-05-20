/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:32:20 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/07 05:12:00 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((y) >= WIN_HEIGHT || (x) >= WIN_WIDTH || \
		(y) < 0.000001 || (x) < 0.000001)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0; 
	while (i < TILE_SIZE)
	{
		j = 0; // change to 1 if you want a grid like map
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(&game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_2d(t_game *game)
{
	int	y;
	int	x;
	
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
								&game->img.endian);
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_square(game, x * TILE_SIZE, y * TILE_SIZE, 0xFF0000); // Red wall
			else
				draw_square(game, x * TILE_SIZE, y * TILE_SIZE, 0xAAAAAA); // Grey floor
			x++;
		}
		y++;
	}
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	draw_player(t_game *game)
{
	my_mlx_pixel_put(&game->img, game->p.px, \
		game->p.py, 0xFFFF00);
	my_mlx_pixel_put(&game->img, game->p.px + 1, \
		game->p.py, 0xFFFF00);
	my_mlx_pixel_put(&game->img, game->p.px, \
		game->p.py + 1, 0xFFFF00);
	my_mlx_pixel_put(&game->img, game->p.px + 1, \
		game->p.py + 1, 0xFFFF00);
	rendering_2d(game);
}

void	rendering_2d(t_game *game)
{
	int		i;
	t_point	end;
	float	angle;
	float	dif;
	
	i = 0;
	angle = game->angle + 30;
	dif = 60.0f / WIN_WIDTH;
	while (i <= WIN_WIDTH)
	{
		end = raycast_custom_angle(game, angle);
		draw_ray_custom_angle(game, end, angle, 0x00FFFF);
		if ((angle - dif) < 0.000001)
			angle = 360;
		angle = fabsf(angle - dif);
		i++;
	}
}

void	draw_ray_custom_angle(t_game *game, t_point point, float angle, int color)
{
	float	dx;
	float	dy;
	t_point	temp;
	t_point	comp;
	
	dx = cosf(angle * PI/180);
	dy = sinf(angle * PI/180);
	temp.px = game->p.px;
	temp.py = game->p.py;
	comp = round_endpoint(temp, angle);
	while (comp.px != point.px || comp.py != point.py)
	{
		if (temp.py > WIN_HEIGHT || temp.px > WIN_WIDTH || temp.py < 0.000001 || temp.px < 0.000001 || \
			(int)((temp.py)/TILE_SIZE) >= game->map_height || \
			(int)((temp.px)/TILE_SIZE) >= game->map_width)
			break ;
		my_mlx_pixel_put(&game->img, temp.px, temp.py, color);
		temp.px += dx;
		temp.py += dy;
		comp = round_endpoint(temp, angle);
	}
}
