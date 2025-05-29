/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:45:27 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/29 21:15:38 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

static t_error	validate_file(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (!filename || len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (ERR_INVALID_FILE);
	return (ERR_NONE);
}

static t_error	parse_line(char *line, t_game *info)
{
	if (line[0] == '\n' || is_empty_line(line))
		return (ERR_NONE);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (parse_textures(line, info));
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (parse_colors(line, info));
	if (line[0] == '1' || line[0] == ' ')
		return (ERR_MALLOC);
	return (ERR_INVALID_MAP);
}

t_error	parse_map_block(t_game *info, char **lines)
{
	t_error	err;

	info->map = read_map(lines);
	if (!info->map)
		return (free_lines(lines), ERR_MALLOC);
	pad_map_lines(info->map, info->map_height, info->map_width);
	err = validate_map(info);
	return (free_lines(lines), err);
}

t_error	parse_file_loop(char **lines, t_game *info)
{
	t_error	err;
	int		i;

	i = -1;
	while (lines[++i])
	{
		err = parse_line(lines[i], info);
		if (err == ERR_MALLOC)
			return (parse_map_block(info, lines));
		if (err != ERR_NONE)
			return (free_lines(lines), err);
	}
	return (free_lines(lines), ERR_INVALID_MAP);
}

t_error	parse_file(const char *filename, t_game *info)
{
	int		fd;
	int		i;
	char	**lines;
	t_error	err;

	i = -1;
	err = validate_file(filename);
	if (err != ERR_NONE)
		return (err);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ERR_INVALID_FILE);
	lines = read_all_lines(fd);
	close(fd);
	if (!lines)
		return (ERR_MALLOC);
	info->map_height = count_map_lines(lines);
	info->map_width = get_map_width(lines);
	if (info->map_height <= 0 || info->map_width <= 0)
		return (free_lines(lines), ERR_INVALID_MAP);
	return (parse_file_loop(lines, info));
}
