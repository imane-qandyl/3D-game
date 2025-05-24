/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:12 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/24 17:50:20 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_map_lines(char **lines)
{
	int	i;
	int	count;
	int	found_map;
	int	len;

	i = 0;
	count = 0;
	found_map = 0;
	while (lines[i])
	{
		len = ft_strlen(lines[i]);
		if (len > 0 && lines[i][len - 1] == '\n')
			lines[i][len - 1] = '\0';
		if (!found_map)
		{
			if (lines[i][0] == '1' || lines[i][0] == ' ')
				found_map = 1;
			else
			{
				i++;
				continue ;
			}
		}
		if (!is_map_line(lines[i]))
			return (-1);
		if (lines[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

int	get_map_width(char **lines)
{
	int	max_width;
	int	found_map;
	int	i;
	int	len;

	max_width = 0;
	found_map = 0;
	i = 0;
	if (!lines)
		return (0);
	while (lines[i])
	{
		if (!found_map && (lines[i][0] == '\0' || ft_strncmp(lines[i], "NO ",
				3) == 0 || ft_strncmp(lines[i], "SO ", 3) == 0
			|| ft_strncmp(lines[i], "WE ", 3) == 0 || ft_strncmp(lines[i],
				"EA ", 3) == 0 || ft_strncmp(lines[i], "F ", 2) == 0
			|| ft_strncmp(lines[i], "C ", 2) == 0))
		{
			i++;
			continue ;
		}
		found_map = 1;
		len = ft_strlen(lines[i]);
		if (len > 0 && lines[i][len - 1] == '\n')
			len--;
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW \n", line[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**read_all_lines(int fd)
{
	char	**lines;
	char	*line;
	int		i;

	lines = malloc(sizeof(char *) * 1024);
	i = 0;
	if (!lines)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		lines[i++] = line;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	return (lines);
}

char	**read_map(char **lines)
{
	int		i;
	int		j;
	int		found_map;
	int		map_lines;
	char	**map;
	int		len;

	i = 0;
	j = 0;
	found_map = 0;
	map_lines = count_map_lines(lines);
	if (map_lines <= 0)
		return (NULL);
	map = malloc(sizeof(char *) * (map_lines + 1));
	if (!map)
		return (NULL);
	while (lines[i] && j < map_lines)
	{
		if (!found_map)
		{
			if (lines[i][0] == '1' || lines[i][0] == ' ')
				found_map = 1;
			else
			{
				i++;
				continue ;
			}
		}
		len = ft_strlen(lines[i]);
		while (len > 0 && (lines[i][len - 1] == '\n' || lines[i][len
			- 1] == ' '))
			len--;
		map[j++] = ft_strdup(lines[i]);
		i++;
	}
	map[j] = NULL;
	return (map);
}

void	pad_map_lines(char **map, int height, int width)
{
	int		y;
	int		len;
	int		i;
	char	*padded;

	y = 0;
	while (y < height)
	{
		len = ft_strlen(map[y]);
		if (len < width)
		{
			padded = malloc(width + 1);
			if (!padded)
				return ;
			ft_memcpy(padded, map[y], len);
			i = len;
			while (i < width)
			{
				padded[i] = ' ';
				i++;
			}
			padded[width] = '\0';
			free(map[y]);
			map[y] = padded;
		}
		y++;
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

t_error	check_player_count(char **map)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = 0;
	j = 0;
	if (!map)
		return (ERR_INVALID_MAP);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (ERR_NO_PLAYER);
	if (player_count > 1)
		return (ERR_DUPLICATE_PLAYER);
	return (ERR_NONE);
}

t_error	validate_map(t_game *info)
{
	t_error	err;
	int		x;
	int		y;
	char	top;
	char	bottom;
	char	left;
	char	right;

	if (!info->map)
		return (ERR_INVALID_MAP);
	err = check_player_count(info->map);
	if (err != ERR_NONE)
		return (err);
	x = 0;
	while (x < info->map_width)
	{
		top = info->map[0][x];
		bottom = info->map[info->map_height - 1][x];
		if ((top != '1' && top != ' ') || (bottom != '1' && bottom != ' '))
			return (ERR_MAP_NOT_CLOSED);
		x++;
	}
	y = 0;
	while (y < info->map_height)
	{
		left = info->map[y][0];
		right = info->map[y][info->map_width - 1];
		if ((left != '1' && left != ' ') || (right != '1' && right != ' '))
			return (ERR_MAP_NOT_CLOSED);
		y++;
	}
	y = 1;
	while (y < info->map_height - 1)
	{
		x = 1;
		while (x < info->map_width - 1)
		{
			if (info->map[y][x] == '0' || info->map[y][x] == 'N'
				|| info->map[y][x] == 'S' || info->map[y][x] == 'E'
				|| info->map[y][x] == 'W')
			{
				if (info->map[y + 1][x] == ' ' || info->map[y - 1][x] == ' '
					|| info->map[y][x + 1] == ' ' || info->map[y][x - 1] == ' ')
					return (ERR_MAP_NOT_CLOSED);
			}
			x++;
		}
		y++;
	}
	return (ERR_NONE);
}
