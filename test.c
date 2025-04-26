#include "includes/cub3d.h"

void	move_player_a(t_game *game, int px, int py)
{
	int	x;
	int	y;
	
	x = -1;
	y = -1;
	if ((game->player_y + py) >= (game->map_height * TILE_SIZE - 4) || \
	(game->player_x + px) >= (game->map_width * TILE_SIZE - 4))
	return ;
	while (++y < 4)
	{
		while (++x < 4)
		{
			// printf("1 : %f\n", ((game->player_x + x) / TILE_SIZE));
			if (game->map[(int)((game->player_y + y) / TILE_SIZE)][(int)((game->player_x + x) / TILE_SIZE)] == '1')
				mlx_pixel_put(game->mlx, game->win, game->player_x + x, game->player_y + y, 0xFF0000);
			else
				mlx_pixel_put(game->mlx, game->win, game->player_x + x, game->player_y + y, 0xAAAAAA);
			mlx_pixel_put(game->mlx, game->win,\
						game->player_x + x + px,\
						game->player_y + y + py, 0xFFFF00);
		}
		x = -1;
	}
	game->player_x += px;
	game->player_y += py;
}


void	move_player_b(t_game *game, float dx, float dy)
{
	int	x;
	int	y;
	
	x = -1;
	y = -1;
	if ((game->player_y + dy) >= WIN_HEIGHT || (game->player_x + dx) >= WIN_WIDTH)
		return ;
	while (++y < 4)
	{
			// printf("1 : %f\n", ((game->player_x + x + dx) / TILE_SIZE));
			if (game->map[(int)((game->player_y + y) / TILE_SIZE)][(int)((game->player_x + x) / TILE_SIZE)] == '1')
				mlx_pixel_put(game->mlx, game->win, game->player_x + x, game->player_y + y, 0xFF0000);
			else
				mlx_pixel_put(game->mlx, game->win, game->player_x + x, game->player_y + y, 0xAAAAAA);
			mlx_pixel_put(game->mlx, game->win,\
						game->player_x + x + dx,\
						game->player_y + y + dy, 0xFFFF00);
	}
	game->player_x += dx;
	game->player_y += dy;
}

void	move_player_1px_a(t_game *game, int steps, float dx, float dy)
{
	while (steps-- > 0)
	{
		if ((game->player_y + dy) >= WIN_HEIGHT || (game->player_x + dx) >= WIN_WIDTH || \
			(game->player_y + dy) < 0 || (game->player_x + dx) < 0)
			return ;
		if (game->map[(int)((game->player_y) / TILE_SIZE)][(int)((game->player_x) / TILE_SIZE)] == '1')
			mlx_pixel_put(game->mlx, game->win, game->player_x, game->player_y, 0xFF0000);
		else
			mlx_pixel_put(game->mlx, game->win, game->player_x, game->player_y, 0xAAAAAA);
		mlx_pixel_put(game->mlx, game->win, game->player_x + dx, \
				game->player_y + dx, 0xFFFF00);
		game->player_x += dx;
		game->player_y += dy;
	}
}


void	move_player(t_game *game, float dx, float dy)
{
	int	x;
	int	y;
	
	x = -1;
	y = -1;
	while (++y < 4)
	{
		while (++x < 4)
		{
			if ((game->player_y + dy) >= WIN_HEIGHT || (game->player_x + dx) >= WIN_WIDTH)
				return ;
			if (game->map[(int)((game->player_y + y) / TILE_SIZE)][(int)((game->player_x + x) / TILE_SIZE)] == '1')
				mlx_pixel_put(game->mlx, game->win, game->player_x + x, game->player_y + y, 0xFF0000);
			else
				mlx_pixel_put(game->mlx, game->win, game->player_x + x, game->player_y + y, 0xAAAAAA);
			// draw_map(game);
			mlx_pixel_put(game->mlx, game->win,\
						game->player_x + x + dx,\
						game->player_y + y + dy, 0xFFFF00);
		}
		x = -1;
	}
	game->player_x += game->pdx;
	game->player_y += game->pdy;
}



float	length_of_raycast_H(t_game *game, float px, float py, double angle) // increment Y 
{
	float	lz;
	int		i;

	printf("here?\n");
	if (angle == 0 || angle == PI)
	return (-1);
	lz = 0;
	printf("----------------\nlz horizontal = %f\npx = %f\npy = %f\nangle = %f\n\n", lz, px, py, angle);
	if (angle > PI && angle <= (2*PI))
	{
		i = (int)py;
		while (i >= 0 && game->map[i][(int)px] != '1')
		{
			printf("inside 0-PI   i = %d\n", i);
			lz += (py - i)/sinf(angle);
			i--;
		}
	}
	else if (angle > 0 && angle < PI)
	{
		i = (int)py + 1;
		while (i <= (WIN_HEIGHT/TILE_SIZE) && game->map[i][(int)px] != '1')
		{
			printf("inside PI-2PI   i = %d\n", i);
			lz += (i - py)/sinf(angle);
			i++;
		}
	}
	printf("lz horizontal = %f\npx = %f\npy = %f\nangle = %f\n----------------\n", lz, px, py, angle);
	return (lz);
}

float	length_of_raycast_H(t_game *game, float px, float py, double angle) // increment Y 
{
	float	lz;
	int		i;

	printf("here?\n");
	if (angle == 0 || angle == PI)
	return (-1);
	lz = 0;
	printf("----------------\nlz horizontal = %f\npx = %f\npy = %f\nangle = %f\n\n", lz, px, py, angle);
	if (angle > 0 && angle < PI)
	{
		i = (int)(py/TILE_SIZE);
		printf("0-PI   i = %dthing = %f\n", i, py - (i * TILE_SIZE));
		while ((py - (i * TILE_SIZE)) > 0 && game->map[((int)py)/TILE_SIZE][((int)px)/TILE_SIZE] != '1')
		{
			printf("inside 0-PI   i = %d\n", i);
			lz += (py - (i * TILE_SIZE))/sinf(angle); // might have to make sinf negative
			i--;
		}
	}
	else if (angle > PI && angle <= (2*PI))
	{
		i = floorf(py/TILE_SIZE) + 1;
		printf("PI-2PI   i = %d\n", i);
		while ((i * TILE_SIZE) < WIN_WIDTH && game->map[(int)py/TILE_SIZE][(int)px/TILE_SIZE] != '1')
		{
			printf("inside PI-2PI   i = %d\n", i);
			lz += ((i * TILE_SIZE) - py)/sinf(angle); // might have to make sinf negative
			i++;
		}
	}
	printf("lz horizontal = %f\npx = %f\npy = %f\nangle = %f\n----------------\n", lz, px, py, angle);
	return (lz);
}



// didnt work well but better, innacurate points and over/undershooting 
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
			ph.py = (int)tempy;
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
			pv.px = (int)tempx;
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




