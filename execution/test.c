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