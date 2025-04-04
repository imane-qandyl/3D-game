/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:19:23 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/04 10:10:37 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(void)
{
	t_game	game;

	game.map = read_map("maps/level1.cub");
	if (!game.map)
	{
		printf("Failed to load map.\n");
		return (1);
	}
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	draw_map(&game);
	mlx_loop(game.mlx);
	free_map(game.map);
	return (0);
}
