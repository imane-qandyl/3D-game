/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 21:08:36 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/29 21:15:38 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

t_error	validate_horizontal_edges(char **map, int width, int height)
{
	int	x;

	x = 0;
	while (x < width)
	{
		if ((map[0][x] != '1' && map[0][x] != ' ')
			|| (map[height - 1][x] != '1' && map[height - 1][x] != ' '))
			return (ERR_MAP_NOT_CLOSED);
		x++;
	}
	return (ERR_NONE);
}

t_error	validate_vertical_edges(char **map, int width, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		if ((map[y][0] != '1' && map[y][0] != ' ')
			|| (map[y][width - 1] != '1' && map[y][width - 1] != ' '))
			return (ERR_MAP_NOT_CLOSED);
		y++;
	}
	return (ERR_NONE);
}

t_error	validate_holes(char **map, int width, int height)
{
	int	x;
	int	y;

	y = 1;
	while (y < height - 1)
	{
		x = 1;
		while (x < width - 1)
		{
			if (ft_strchr("0NSEW", map[y][x])
				&& (map[y + 1][x] == ' ' || map[y - 1][x] == ' '
				|| map[y][x + 1] == ' ' || map[y][x - 1] == ' '))
				return (ERR_MAP_NOT_CLOSED);
			x++;
		}
		y++;
	}
	return (ERR_NONE);
}

t_error	validate_map(t_game *info)
{
	t_error	err;

	if (!info->map)
		return (ERR_INVALID_MAP);
	err = check_player_count(info->map);
	if (err != ERR_NONE)
		return (err);
	err = validate_horizontal_edges(info->map, info->map_width,
			info->map_height);
	if (err != ERR_NONE)
		return (err);
	err = validate_vertical_edges(info->map, info->map_width,
			info->map_height);
	if (err != ERR_NONE)
		return (err);
	err = validate_holes(info->map, info->map_width,
			info->map_height);
	return (err);
}

int	count_map_lines(char **lines)
{
	int	i;
	int	count;
	int	found;

	i = 0;
	count = 0;
	found = 0;
	while (lines[i])
	{
		strip_newline(lines[i]);
		if (!found && (lines[i][0] == '1' || lines[i][0] == ' '))
			found = 1;
		if (!found)
		{
			i++;
			continue ;
		}
		if (!is_map_line(lines[i]))
			return (-1);
		if (lines[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}
