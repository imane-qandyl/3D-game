/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:12 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/04 11:26:23 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINES 100

char	**read_map(const char *filename)
{
	FILE	*file;
	char	**map;
	size_t	i;
	char	*line;
	size_t	len;

	file = fopen(filename, "r");
	if (!file)
		return (NULL);
	map = malloc(sizeof(char *) * (MAX_LINES + 1));
	if (!map)
		return (NULL);
	i = 0;
	line = NULL;
	len = 0;
	ssize_t read; // number of bytes read by getline.
	//Removes the trailing newline character from each line (if it exists).
	//
	while ((read = getline(&line, &len, file)) != -1 && i < MAX_LINES)
	{
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		map[i++] = strdup(line);
	}
	map[i] = NULL;
	free(line);
	fclose(file);
	return (map);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		printf("%s\n", map[i]);
	i++;
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i]);
	free(map);
}