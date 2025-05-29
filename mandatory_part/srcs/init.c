/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:48:11 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/29 19:30:57 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_angle(char c)
{
	if (c == 'S')
		return (90);
	if (c == 'W')
		return (180);
	if (c == 'N')
		return (270);
	if (c == 'E')
		return (0);
	write(1, "this shouldnt show\n", 19);
	return (0);
}

void	exec_init(t_game *game)
{
	init_point(&game->p);
	game->player_dir = get_player_direction(game);
	game->angle = get_angle(game->player_dir);
	get_player_position(game);
	game->dx = cos(game->angle * (PI / 180));
	game->dy = sin(game->angle * (PI / 180));
	game->key.w = false;
	game->key.a = false;
	game->key.s = false;
	game->key.d = false;
	game->key.left = false;
	game->key.right = false;
	game->img.img = NULL;
	game->minimap_tile_size = 0;
}

int	load_textures(t_game *game)
{
	int	width;
	int	height;

	game->no_texture = mlx_xpm_file_to_image(game->mlx,
			game->no_texture, &width, &height);
	if (!game->no_texture)
		return (0);
	game->tex_width = width;
	game->tex_height = height;
	game->so_texture = mlx_xpm_file_to_image(game->mlx,
			game->so_texture, &width, &height);
	if (!game->so_texture || width != game->tex_width
		|| height != game->tex_height)
		return (0);
	game->we_texture = mlx_xpm_file_to_image(game->mlx,
			game->we_texture, &width, &height);
	if (!game->we_texture || width != game->tex_width
		|| height != game->tex_height)
		return (0);
	game->ea_texture = mlx_xpm_file_to_image(game->mlx,
			game->ea_texture, &width, &height);
	if (!game->ea_texture || width != game->tex_width
		|| height != game->tex_height)
		return (0);
	return (1);
}
