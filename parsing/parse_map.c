/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:12 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/26 18:40:30 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int count_map_lines(char **lines)
{
    int i = 0;
    int count = 0;
    int found_map = 0;

    while (lines[i])
    {
        int len = ft_strlen(lines[i]);
        if (len > 0 && lines[i][len - 1] == '\n')
            lines[i][len - 1] = '\0';

        if (!found_map)
        {
            if (lines[i][0] == '1' || lines[i][0] == ' ')
                found_map = 1;
            else
            {
                i++;
                continue;
            }
        }

        if (!is_map_line(lines[i]))
            return (-1);

        if (lines[i][0] != '\0')
            count++;
        i++;
    }
    return count;
}

int get_map_width(char **lines)
{
    int max_width = 0;
    int found_map = 0;
    int i = 0;

    if (!lines)
        return 0;

    while (lines[i])
    {
        if (!found_map && (lines[i][0] == '\n' || lines[i][0] == 'N' || lines[i][0] == 'S'
            || lines[i][0] == 'W' || lines[i][0] == 'E' || lines[i][0] == 'F' || lines[i][0] == 'C'))
        {
            i++;
            continue;
        }

        found_map = 1;

        int len = ft_strlen(lines[i]);
        if (len > 0 && lines[i][len - 1] == '\n')
            len--;

        if (len > max_width)
            max_width = len;

        i++;
    }
    return max_width;
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
//including texture, floor, ceiling, map lines, empty lines
char **read_all_lines(int fd)
{
	char **lines = malloc(sizeof(char *) * 1024); // or dynamically grow
	char *line;
	int i = 0;

	if (!lines)
		return NULL;

	while ((line = get_next_line(fd)))
	{
		lines[i++] = line;
	}
	lines[i] = NULL;
	return lines;
}

char **read_map(char **lines)
{
    int     i = 0, j = 0;
    int     found_map = 0;
    int     map_lines = count_map_lines(lines);
    char    **map;

    if (map_lines <= 0)
        return NULL;

    map = malloc(sizeof(char *) * (map_lines + 1));
    if (!map)
        return NULL;

    while (lines[i] && j < map_lines)
    {
        if (!found_map)
        {
            if (lines[i][0] == '1' || lines[i][0] == ' ')
                found_map = 1;
            else
            {
                i++;
                continue;
            }
        }

        int len = ft_strlen(lines[i]);
        if (len > 0 && lines[i][len - 1] == '\n')
            lines[i][len - 1] = '\0';

        map[j++] = ft_strdup(lines[i]);
        i++;
    }
    map[j] = NULL;
    return map;
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
t_error check_player_count(char **map)
{
    int player_count = 0;
    int i = 0, j;

    if (!map)
    return (ERR_INVALID_MAP);

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S'
                || map[i][j] == 'E' || map[i][j] == 'W')
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
t_error validate_map(t_game *info)
{
    t_error err;

    if (!info->map)
        return (ERR_INVALID_MAP);
    printf("Debug 1\n");
    err = check_player_count(info->map);
    if (err != ERR_NONE)
        return (err);
    // Check borders - treat spaces as equivalent to walls for validation Top and bottom rows must be entirely '1' or ' '
    for (int x = 0; x < info->map_width; x++) {
        char top = info->map[0][x];
        char bottom = info->map[info->map_height-1][x];
        if ((top != '1' && top != ' ') || (bottom != '1' && bottom != ' '))
            return (ERR_MAP_NOT_CLOSED);
    }
    //Left and right columns must also be '1' or ' '.
	printf("Debug 2\n");

    for (int y = 0; y < info->map_height; y++) {
        char left = info->map[y][0];
        char right = info->map[y][info->map_width-1];
        if ((left != '1' && left != ' ') || (right != '1' && right != ' ')) {
			printf("LOOK IMANE, LOOK! %d\n", info->map_width);
			printf("left was %c and right was this %c\n", left, right);
			return (ERR_MAP_NOT_CLOSED);
		}
    }
	printf("Debug 3\n");

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
	printf("Debug 4\n");

    return (ERR_NONE);
}