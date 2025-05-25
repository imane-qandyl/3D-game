/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:03:47 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/25 21:02:37 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	destroy_texture(void *mlx, void *texture)
{
	if (mlx && texture)
		mlx_destroy_image(mlx, texture);
}

static void	free_texture(char **texture)
{
	if (*texture)
		free(*texture);
}

void	free_map_info(t_game *info)
{
	int	i;

	free_texture(&info->no_texture);
	free_texture(&info->so_texture);
	free_texture(&info->we_texture);
	free_texture(&info->ea_texture);
	destroy_texture(info->mlx, info->no_texture);
	destroy_texture(info->mlx, info->so_texture);
	destroy_texture(info->mlx, info->we_texture);
	destroy_texture(info->mlx, info->ea_texture);
	if (info->map)
	{
		i = 0;
		while (i < info->map_height)
			free(info->map[i++]);
		i++;
		free(info->map);
	}
	init_map_info(info);
}

void	free_lines(char **lines)
{
	int	i;

	i = 0;
	if (!lines)
		return ;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

int	is_empty_line(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}
