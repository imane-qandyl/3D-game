/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:12 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/11 17:25:18 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int count_map_lines(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    int count = 0;
    int found_map = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1)
    {
        // Trim newline
        if (read > 0 && line[read - 1] == '\n')
            line[read - 1] = '\0';

        if (!found_map)
        {
            if (line[0] == '1' || line[0] == ' ')
                found_map = 1;
            else
                continue;
        }

        if (!is_map_line(line))
        {
            
            rewind(file);
			free(line);
            return (-1);
        }

        if (line[0] != '\0') // Only skip truly empty lines
            count++;
    }

    //printf("count_map_lines: %d\n", count);
    free(line);
    rewind(file);
    return count;
}
//returns the width (number of columns)
int	get_map_width(FILE *file)
{
	char	*line;
	size_t	len; //total number of characters in the line
	int		max_width;
	int		found_map;

	max_width = 0;
	found_map = 0;
	line = NULL;
	len = 0;
	while (getline(&line, &len, file) != -1)
	{
		// Skip empty lines and texture/color configurations before map
		if (!found_map && (line[0] == '\n' || line[0] == 'N' || line[0] == 'S'
				|| line[0] == 'W' || line[0] == 'E' || line[0] == 'F'
				|| line[0] == 'C'))
			continue ;
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
int is_map_line(char *line)
{
    int i = 0;
    
    while (line[i])
    {
        if (!ft_strchr("01NSEW\n", line[i]))
            return (0);
        i++;
    }
    return (1);
}

char	**read_map(const char *filename)
{
	FILE	*file;
	char	*line;
	size_t	len;
	int		line_index;
	int		found_map;
	ssize_t	read;
	char	**map;

	file = fopen(filename, "r");
	if (!file)
		return (NULL);
	int map_lines = count_map_lines(file);
	//printf("map_lines = %d\n",map_lines);
	if (map_lines <= 0)
	{
		fclose(file);
		return (NULL);
	}
	map = malloc(sizeof(char *) * (map_lines + 1));
	if (!map)
		return (NULL);
	
	line_index = 0;
	found_map = 0;
	line = NULL;
	len = 0;
	while ((read =getline(&line, &len, file)) != -1)
	{
		if (!found_map)
		{
			if (line[0] == '1' || line[0] == ' ')
				found_map = 1;
			else
				continue;
		}
		// Trim newline
		if (read > 0 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		map[line_index++] = strdup(line);
	}
	free(line);
	map[line_index] = NULL;
	fclose(file);
	return (map);
}


void	free_map(char **map)
{
	int i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

t_error validate_map(t_game *info)
{
    if (!info->map)
        return (ERR_INVALID_MAP);
    // Check borders
    for (int x = 0; x < info->map_width; x++) {
        if (info->map[0][x] != '1' || info->map[info->map_height-1][x] != '1')
            return (ERR_MAP_NOT_CLOSED);
    }
    
    for (int y = 0; y < info->map_height; y++) {
        if (info->map[y][0] != '1' || info->map[y][info->map_width-1] != '1')
            return (ERR_MAP_NOT_CLOSED);
    }
    
    // Check inner spaces
    for (int y = 1; y < info->map_height - 1; y++) {
        for (int x = 1; x < info->map_width - 1; x++) {
            if (info->map[y][x] == '0' || info->map[y][x] == 'N' || 
                info->map[y][x] == 'S' || info->map[y][x] == 'E' || 
                info->map[y][x] == 'W') {
                // Check all 4 directions
                if (info->map[y+1][x] == ' ' || info->map[y-1][x] == ' ' ||
                    info->map[y][x+1] == ' ' || info->map[y][x-1] == ' ')
                    return (ERR_MAP_NOT_CLOSED);
            }
        }
    }
    
    return (ERR_NONE);
}