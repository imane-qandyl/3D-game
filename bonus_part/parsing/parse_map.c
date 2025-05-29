/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:12 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/29 21:15:38 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

void	strip_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	is_config_line(char *line)
{
	return (line[0] == '\0' || ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}

int	get_map_width(char **lines)
{
	int	max;
	int	len;
	int	i;
	int	found;

	max = 0;
	i = 0;
	found = 0;
	while (lines[i])
	{
		if (!found && is_config_line(lines[i]))
		{
			i++;
			continue ;
		}
		found = 1;
		len = ft_strlen(lines[i]);
		if (len > 0 && lines[i][len - 1] == '\n')
			len--;
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static void	copy_map_lines(char **lines, char **map, int count)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	j = 0;
	found = 0;
	while (lines[i] && j < count)
	{
		if (!found && (lines[i][0] == '1' || lines[i][0] == ' '))
			found = 1;
		if (!found)
			i++;
		else
			map[j++] = ft_strdup(lines[i++]);
	}
	map[j] = NULL;
}

char	**read_map(char **lines)
{
	char	**map;
	int		count;

	count = count_map_lines(lines);
	if (count <= 0)
		return (NULL);
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	copy_map_lines(lines, map, count);
	return (map);
}
