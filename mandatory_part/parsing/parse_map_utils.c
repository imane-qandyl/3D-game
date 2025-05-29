/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:26:02 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/25 21:30:14 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	pad_map_lines(char **map, int height, int width)
{
	int		y;
	int		i;
	int		len;
	char	*p;

	y = -1;
	while (++y < height)
	{
		len = ft_strlen(map[y]);
		if (len < width)
		{
			p = malloc(width + 1);
			if (!p)
				return ;
			ft_memcpy(p, map[y], len);
			i = len;
			while (i < width)
				p[i++] = ' ';
			p[width] = '\0';
			free(map[y]);
			map[y] = p;
		}
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
	int	i;
	int	j;
	int	player_count;

	if (!map)
		return (ERR_INVALID_MAP);
	i = -1;
	player_count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				player_count++;
	}
	if (player_count == 0)
		return (ERR_NO_PLAYER);
	if (player_count > 1)
		return (ERR_DUPLICATE_PLAYER);
	return (ERR_NONE);
}
