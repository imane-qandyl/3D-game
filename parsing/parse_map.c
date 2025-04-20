/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:12 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/20 21:45:52 by imqandyl         ###   ########.fr       */
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
				|| line[0] == 'C' ))
			continue ;
		found_map = 1;
		
		// Remove newline
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
        if (!ft_strchr("01NSEW \n", line[i]))
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
//padding logic → 1111␣␣
void pad_map_lines(char **map, int height, int width)
{
    for (int y = 0; y < height; y++)
    {
        int len = ft_strlen(map[y]);
        if (len < width)
        {
            char *padded = malloc(width + 1);
            ft_memcpy(padded, map[y], len);
            for (int i = len; i < width; i++)
                padded[i] = ' ';
            padded[width] = '\0';
            free(map[y]);
            map[y] = padded;
        }
    }
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
     
    // Check borders - treat spaces as equivalent to walls for validation Top and bottom rows must be entirely '1' or ' '
    for (int x = 0; x < info->map_width; x++) {
        char top = info->map[0][x];
        char bottom = info->map[info->map_height-1][x];
        if ((top != '1' && top != ' ') || (bottom != '1' && bottom != ' '))
            return (ERR_MAP_NOT_CLOSED);
    }
    //Left and right columns must also be '1' or ' '.

    for (int y = 0; y < info->map_height; y++) {
        char left = info->map[y][0];
        char right = info->map[y][info->map_width-1];
        if ((left != '1' && left != ' ') || (right != '1' && right != ' '))
            return (ERR_MAP_NOT_CLOSED);
    }
    
    // Check inner spaces
    for (int y = 1; y < info->map_height - 1; y++) {
        for (int x = 1; x < info->map_width - 1; x++) {
            if (info->map[y][x] == '0' || info->map[y][x] == 'N' || 
                info->map[y][x] == 'S' || info->map[y][x] == 'E' || 
                info->map[y][x] == 'W') {
                // Check all 4 directions space adjacent to it
                if (info->map[y+1][x] == ' ' || info->map[y-1][x] == ' ' ||
                    info->map[y][x+1] == ' ' || info->map[y][x-1] == ' ')
					return (ERR_MAP_NOT_CLOSED);
					//printf("IMANE");
				}
        }
    }
    
    return (ERR_NONE);
}
