/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:12 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/08 09:31:35 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int count_map_lines(FILE *file)
{
	char	*line;
	size_t	len;
	int		count;
	int		found_map;

	count = 0;
	found_map = 0;
	line = NULL;
	len = 0;
	while (getline(&line, &len, file) != -1)
	{
		// Skip empty lines and texture/color configurations before map
		if (!found_map && (line[0] == '\n' || line[0] == 'N' || line[0] == 'S' ||
			line[0] == 'W' || line[0] == 'E' || line[0] == 'F' || line[0] == 'C'))
			continue;
		found_map = 1;
		count++;
	}
	free(line);
	rewind(file);
	return (count);
}

static int get_map_width(FILE *file)
{
	char	*line;
	size_t	len;
	int		max_width;
	int		found_map;

	max_width = 0;
	found_map = 0;
	line = NULL;
	len = 0;
	while (getline(&line, &len, file) != -1)
	{
		// Skip empty lines and texture/color configurations before map
		if (!found_map && (line[0] == '\n' || line[0] == 'N' || line[0] == 'S' ||
			line[0] == 'W' || line[0] == 'E' || line[0] == 'F' || line[0] == 'C'))
			continue;
		found_map = 1;
		if (strlen(line) > (size_t)max_width)
			max_width = strlen(line);
		if (line[max_width - 1] == '\n')
			max_width--;
	}
	free(line);
	rewind(file);
	return (max_width);
}

static int is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' &&
			line[i] != 'W' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char **read_map(const char *filename)
{
	FILE	*file;
	char	**map;
	char	*line;
	size_t	len;
	int		i;
	int		height;
	int		width;
	int		found_map;

	file = fopen(filename, "r");
	if (!file)
		return (NULL);

	height = count_map_lines(file);
	width = get_map_width(file);

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
	{
		fclose(file);
		return (NULL);
	}

	i = 0;
	found_map = 0;
	line = NULL;
	len = 0;
	while (getline(&line, &len, file) != -1)
	{
		// Skip empty lines and texture/color configurations before map
		if (!found_map && (line[0] == '\n' || line[0] == 'N' || line[0] == 'S' ||
			line[0] == 'W' || line[0] == 'E' || line[0] == 'F' || line[0] == 'C'))
			continue;

		if (!is_map_line(line))
			continue;

		found_map = 1;
		// Remove newline if present
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';

		map[i] = strdup(line);
		if (!map[i])
		{
			while (i > 0)
				free(map[--i]);
			free(map);
			free(line);
			fclose(file);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;

	free(line);
	fclose(file);
	return (map);
}

void print_map(char **map)
{
	int	i;

	if (!map)
		return;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void free_map(char **map)
{
	int	i;

	if (!map)
		return;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}