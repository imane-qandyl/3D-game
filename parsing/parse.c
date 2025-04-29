/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:03:47 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/29 09:11:41 by lalwafi          ###   ########.fr       */
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
	info->p.px = -1;
	info->p.py = -1;
	memset(info->floor_color, 0, sizeof(info->floor_color));
	memset(info->ceiling_color, 0, sizeof(info->ceiling_color));
}

void	free_map_info(t_game *info)
{
	int i;
	if (info->no_texture)
		free(info->no_texture);
	if (info->so_texture)
		free(info->so_texture);
	if (info->we_texture)
		free(info->we_texture);
	if (info->ea_texture)
		free(info->ea_texture);
	if (info->mlx)
	{
		if (info->no_texture)
			mlx_destroy_image(info->mlx, info->no_texture);
		if (info->so_texture)
			mlx_destroy_image(info->mlx, info->so_texture);
		if (info->we_texture)
			mlx_destroy_image(info->mlx, info->we_texture);
		if (info->ea_texture)
			mlx_destroy_image(info->mlx, info->ea_texture);
	}
	if (info->map)
	{
		i = 0;
		while(i < info->map_height)
			free(info->map[i]);
		i++;
		free(info->map);
	}
	init_map_info(info);
}

static int	is_empty_line(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

t_error	parse_file(const char *filename, t_game *info)
{
	FILE	*file;
	char	*line;
	size_t	len;
	t_error	err;

	if (!filename || !info)
		return (ERR_INVALID_FILE);
	// Check file extension
	if (strlen(filename) < 4 || strcmp(filename + strlen(filename) - 4,
			".cub") != 0)
		return (ERR_INVALID_FILE);
	file = fopen(filename, "r");
	if (!file)
		return (ERR_INVALID_FILE);
	line = NULL;
	len = 0;
	while (getline(&line, &len, file) != -1)
	{
		if (is_empty_line(line))
			continue ;
		// Remove newline if present
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		// Parse textures and colors first
		if (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0
			|| strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0)
		{
			if ((err = parse_textures(line, info)) != ERR_NONE)
			{
				free(line);
				fclose(file);
				return (err);
			}
		}
		else if (line[0] == 'F' || line[0] == 'C')
		{
			if ((err = parse_colors(line, info)) != ERR_NONE)
			{
				free(line);
				fclose(file);
				return (err);
			}
		}
		// TODO: Add map parsing once textures and colors are done
	}
	free(line);
	fclose(file);
	return (ERR_NONE);
}

void	print_error(t_error error)
{
	const char *error_messages[] = {"No error", "Invalid file",
		"Missing texture", "Invalid color format", "Invalid map format",
		"Invalid player count", "Map not properly closed",
		"Memory allocation error"};

	printf("Error\n%s\n", error_messages[error]);
}
