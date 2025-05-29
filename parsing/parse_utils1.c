/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 21:03:53 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/25 21:03:55 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_map_info(t_game *info)
{
	info->no_texture = NULL;
	info->so_texture = NULL;
	info->we_texture = NULL;
	info->ea_texture = NULL;
	info->map = NULL;
	info->map_width = 0;
	info->map_height = 0;
	info->player_dir = '\0';
	info->p.x = -1;
	info->p.y = -1;
	ft_memset(info->floor_color, -1, sizeof(info->floor_color));
	ft_memset(info->ceiling_color, -1, sizeof(info->ceiling_color));
}

void	print_error(t_error error)
{
	const char	*error_messages[] = {"No error", "Memory allocation error",
		"Invalid file", "Missing texture", "Invalid color format",
		"Invalid map format", "Invalid player count", "Map not properly closed",
		"Duplicate texture", "Duplicate colors", "Duplicate player",
		"No player"};

	printf("Error : %s\n", error_messages[error]);
}
