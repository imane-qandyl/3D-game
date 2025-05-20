#include "../includes/cub3d.h"

void	init_point(t_point *point)
{
	point->angle = 0;
	point->dx = 0;
	point->dy = 0;
	point->face = '\0';
	point->length = 0;
	point->px = 0;
	point->py = 0;
	point->ray_num = 0;
	point->dist_x = 0;
	point->dist_y = 0;
}

t_point	raycast_take_two(t_game *game, double ray_angle)
{
	t_point	end;

	init_point(&end);
	end.px = game->p.px;
	end.py = game->p.py;
	end.angle = ray_angle;
	end.dx = cos(ray_angle * PI/180);
	end.dy = sin(ray_angle * PI/180);
	while (end.py <= WIN_HEIGHT && end.px <= WIN_WIDTH)
	{
		end.dist_x += end.dx;
		end.dist_y += end.dy;
		end.px += end.dx;
		end.py += end.dy;
		if ()
	}
}