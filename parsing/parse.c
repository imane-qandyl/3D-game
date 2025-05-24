/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:03:47 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/24 18:04:58 by imqandyl         ###   ########.fr       */
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

void	free_map_info(t_game *info)
{
	int	i;

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

t_error	parse_file(const char *filename, t_game *info)
{
	int		fd;
	char	**lines;
	t_error	err;
	char	*line;
	int		i;

	lines = NULL;
	err = ERR_NONE;
	if (!filename || !info)
		return (ERR_INVALID_FILE);
	if (ft_strlen(filename) < 4
		|| ft_strncmp(filename + ft_strlen(filename) - 4, ".cub", 4) != 0)
		return (ERR_INVALID_FILE);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ERR_INVALID_FILE);
	lines = read_all_lines(fd);
	if (!lines)
	{
		close(fd);
		return (ERR_MALLOC);
	}
	close(fd);
	info->map_height = count_map_lines(lines);
	info->map_width = get_map_width(lines);
	printf("height:%d\n", info->map_height);
	printf("width:%d\n", info->map_width);
	if (info->map_height <= 0 || info->map_width <= 0)
	{
		free_lines(lines);
		return (ERR_INVALID_MAP);
	}
	i = 0;
	while (lines[i])
	{
		line = lines[i];
		if (line[0] == '\n' || is_empty_line(line))
		{
			i++;
			continue ;
		}
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0
			|| ft_strncmp(line, "EA ", 3) == 0)
		{
			err = parse_textures(line, info);
			if (err != ERR_NONE)
			{
				free_lines(lines);
				return (err);
			}
		}
		else if (ft_strncmp(line, "F ", 2) == 0
			|| ft_strncmp(line, "C ", 2) == 0)
		{
			err = parse_colors(line, info);
			if (err != ERR_NONE)
			{
				free_lines(lines);
				return (ERR_INVALID_COLOR);
			}
		}
		else if (line[0] == '1' || line[0] == ' ')
		{
			info->map = read_map(lines);
			if (!info->map)
			{
				free_lines(lines);
				return (ERR_MALLOC);
			}
			pad_map_lines(info->map, info->map_height, info->map_width);
			if (info->map_width == 0 || info->map_height == 0)
			{
				free_lines(lines);
				return (ERR_INVALID_MAP);
			}
			err = validate_map(info);
			free_lines(lines);
			return (err);
		}
		else
		{
			free_lines(lines);
			return (ERR_INVALID_MAP);
		}
		i++;
	}
	free_lines(lines);
	return (ERR_INVALID_MAP);
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

void	print_error(t_error error)
{
	const char	*error_messages[] = {"No error", "Memory allocation error",
		"Invalid file", "Missing texture", "Invalid color format",
		"Invalid map format", "Invalid player count", "Map not properly closed",
		"Duplicate texture", "Duplicate colors", "Duplicate player",
		"No player"};

	printf("Error : %s\n", error_messages[error]);
}
