/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:51:27 by lalwafi           #+#    #+#             */
/*   Updated: 2025/05/08 15:24:57 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_background(t_game *game, int sky, int floor)
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

void	dda_only_3d(t_game *game)
{
	int		i;
	t_point	end;
	int		line_width;
	int		repeat;
	
	i = 30;
	line_width = 0;
	while (i >= -30)
	{
		repeat = WIN_WIDTH/60;
		end = just_raycast_custom_angle(game, (game->angle + i));
		while (repeat > 0)
			draw_line(game, end, line_width + repeat--, 0x090c66);
		i--;
		line_width += WIN_WIDTH/60;
	}
}

static char	direction_looking_at(t_game *game, t_point p)
{
	if (game->map[(int)((p.py + 1)/TILE_SIZE)][(int)(p.px/TILE_SIZE)] == '1')
		return('S');
	else if (game->map[(int)((p.py - 1)/TILE_SIZE)][(int)(p.px/TILE_SIZE)] == '1')
		return('N');
	else if (game->map[(int)(p.py/TILE_SIZE)][(int)((p.px + 1)/TILE_SIZE)] == '1')
		return('E');
	else if (game->map[(int)(p.py/TILE_SIZE)][(int)((p.px - 1)/TILE_SIZE)] == '1')
		return('W');
	return ('W');
	// printf("px = %f    py = %f     looking WEST\n", p.px, p.py);
}

void	draw_line(t_game *game, t_point end, int location, int color)
{
	int	line_length;
	int	line_location;

	(void)color;
	line_length = end.length;
	if (line_length < 5)
		line_length = 320;
	else
		line_length = (320*TILE_SIZE) / line_length;
	// line_length = line_length * cos(game->angle + (location - 30));
	// printf("line_length before  = %d\n",line_length);
	if (line_length > WIN_HEIGHT)
		line_length = WIN_HEIGHT;
	line_location = -line_length + (line_length/2);
	while (line_length-- > 0)
	{
		if (direction_looking_at(game, end) == 'N')
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0xe342f5);
		else if (direction_looking_at(game, end) == 'S')
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0x8e199c);
		else if (direction_looking_at(game, end) == 'E')
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0xe38aed);
		else if (direction_looking_at(game, end) == 'W')
			my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, 0x8b4494);
		// printf("line_length = %d           line_location = %d\n", line_length, line_location);
		// my_mlx_pixel_put(&game->img, location, (WIN_HEIGHT/2) + line_location++, color);
	}
}
