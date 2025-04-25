/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:49:10 by lalwafi           #+#    #+#             */
/*   Updated: 2025/04/24 21:31:22 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


t_point	length_of_raycast_H(t_game *game) // increment Y 
{
	float	lx;
	t_point	ph;

	ph.px = WIN_WIDTH;
	ph.py = WIN_HEIGHT;
	if (game->angle == 0 || game->angle == 180 || game->angle == 360)
		return(ph);
	lx = 0;
	printf("------------------------ H\npx = %f\npy = %f\nangle = %f\n\n", game->p.px, game->p.py, game->angle);
	if (game->angle > 180 && game->angle <= 360)
	{
		ph.py = (int)(game->p.py/TILE_SIZE) * TILE_SIZE;
		lx = fabsf(ph.py - game->p.py) / (tanf(game->angle * PI/180)) * -1;
		ph.px = fabsf(lx - game->p.px);
		printf("ph.px = %f\nph.py = %f\nlx = %f\n\n", ph.px, ph.py, lx);
		while (ph.py > 0 && ph.px > 0 \
			&& ph.py < WIN_HEIGHT && ph.px < WIN_WIDTH \
			&& (int)((ph.py + TILE_SIZE)/TILE_SIZE) < game->map_height && (int)(ph.px/TILE_SIZE) < game->map_width \
			&& game->map[(int)((ph.py + TILE_SIZE)/TILE_SIZE)][((int)(ph.px/TILE_SIZE))] != '1')
		{
			ph.py -= TILE_SIZE;
			lx = fabsf(ph.py - game->p.py) / (tanf(game->angle * PI/180)) * -1;
			ph.px = fabsf(lx - game->p.px);
			printf("ph.px = %f\nph.py = %f\nlx = %f\n\n", ph.px, ph.py, lx);
		}
	}
	else if (game->angle > 0 && game->angle < 180)
	{
		ph.py = (int)(game->p.py/TILE_SIZE) * TILE_SIZE + 1;
		lx = fabsf(ph.py - game->p.py) / (tanf(game->angle * PI/180)) * -1;
		ph.px = fabsf(lx - game->p.px);
		while (ph.py > 0 && ph.px > 0 \
			&& ph.py < WIN_HEIGHT && ph.px < WIN_WIDTH \
			&& game->map[(int)((ph.py - TILE_SIZE)/TILE_SIZE)][((int)(ph.px/TILE_SIZE))] != '1')
		{
			ph.py += TILE_SIZE;
			lx = fabsf(ph.py - game->p.py) / (tanf(game->angle * PI/180)) * -1;
			ph.px = fabsf(lx - game->p.px);
		}
	}
	printf("------------------------ H\npx = %f\npy = %f\n new_x = %f\n new_y = %f\nangle = %f\n\n", game->p.px, game->p.py, ph.px, ph.py, game->angle);
	return (ph);
}


t_point horizontal_raycast(t_game *game)
{
	t_point	ph;
	float	tempx;
	float	tempy;

	ph.px = WIN_WIDTH;
	ph.py = WIN_HEIGHT;
	tempx = game->p.px;
	tempy = game->p.py;
	if (game->angle == 0 || game->angle == 180 || game->angle == 360)
		return(ph);
	while (game->map[(int)(tempy/TILE_SIZE)][(int)(tempx/TILE_SIZE)])
	{
		if (((int)tempy % TILE_SIZE) == 0)
		{
			ph.px = tempx;
			ph.py = tempy;
		}
		if ((tempy + game->pdy) >= WIN_HEIGHT || (tempx + game->pdx) >= WIN_WIDTH || \
			(tempy + game->pdy) < 0 || (tempx + game->pdx) < 0 || \
			(int)((tempy + game->pdy)/TILE_SIZE) >= game->map_height || \
			(int)((tempx + game->pdx)/TILE_SIZE) >= game->map_width)
			break ;
		tempx = (game->pdx + tempx);
		tempy = (game->pdy + tempy);
	}
	printf("----- Horizontal ----- final phpy = %f     phpx = %f\n", ph.py, ph.px);
	return (ph);
}

t_point vertical_raycast(t_game *game)
{
	t_point	pv;
	float	tempx;
	float	tempy;

	pv.px = WIN_WIDTH;
	pv.py = WIN_HEIGHT;
	tempx = game->p.px;
	tempy = game->p.py;
	if (game->angle == 270 || game->angle == 90)
		return(pv);
	while (game->map[(int)(tempy/TILE_SIZE)][(int)(tempx/TILE_SIZE)])
	{
		if (((int)tempx % TILE_SIZE) == 0)
		{
			pv.px = tempx;
			pv.py = tempy;
		}
		if ((tempy + game->pdy) >= WIN_HEIGHT || (tempx + game->pdx) >= WIN_WIDTH || \
			(tempy + game->pdy) < 0 || (tempx + game->pdx) < 0 || \
			(int)((tempy + game->pdy)/TILE_SIZE) >= game->map_height || \
			(int)((tempx + game->pdx)/TILE_SIZE) >= game->map_width)
			break ;
		tempx = (game->pdx + tempx);
		tempy = (game->pdy + tempy);
	}
	printf("------ Vertical ------ final pvpy = %f     pvpx = %f\n", pv.py, pv.px);
	return (pv);
}

t_point	which_ray_shorter(t_game *game, t_point ph, t_point pv)
{
	float	lh;
	float	lv;

	lh = fabsf(game->p.px - ph.px) + fabsf(game->p.py - ph.py);
	lv = fabsf(game->p.px - pv.px) + fabsf(game->p.py - pv.py);
	if (lh <= lv)
		return (ph);
	return (pv);
}

void	draw_ray(t_game *game, t_point point)
{
	float	dx;
	float	dy;

	dx = game->pdx + game->p.px;
	dy = game->pdy + game->p.py;
	
	while ((int)dx != (int)point.px && (int)dx != (int)point.px)
	{
		printf("----------ray---------\ndx = %f\ndy = %f\npointx = %f\npointy = %f\n----------ray---------\n", dx, dy, point.px, point.py);
		my_mlx_pixel_put(&game->img, dx, \
			dy, 0x0000FF);
		dx += game->pdx;
		dy += game->pdy;
	}
}

void	dda_thing(t_game *game)
{
	draw_ray(game, which_ray_shorter(game, horizontal_raycast(game), vertical_raycast(game)));
}
