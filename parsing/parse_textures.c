/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:48:11 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/08 08:53:21 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int validate_texture_file(const char *path)
{
    FILE *file;

    if (!path)
        return (0);
    file = fopen(path, "r");
    if (!file)
        return (0);
    fclose(file);
    return (1);
}

static char *extract_path(const char *line)
{
    char *path;
    int i;
    int start;

    // Skip identifier and whitespace
    i = 2;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    start = i;
    
    // Find end of path
    while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
        i++;
    
    // Allocate and copy path
    path = (char *)malloc(sizeof(char) * (i - start + 1));
    if (!path)
        return (NULL);
    strncpy(path, line + start, i - start);
    path[i - start] = '\0';
    
    return (path);
}

t_error parse_textures(char *line, t_game *info)
{
    char *path;

    if (!line || !info)
        return (ERR_INVALID_FILE);

    path = extract_path(line);
    if (!path)
        return (ERR_MALLOC);

    if (!validate_texture_file(path))
    {
        free(path);
        return (ERR_MISSING_TEXTURE);
    }

    // Assign texture path based on identifier
    if (strncmp(line, "NO ", 3) == 0)
    {
        if (info->no_texture)
            free(info->no_texture);
        info->no_texture = path;
    }
    else if (strncmp(line, "SO ", 3) == 0)
    {
        if (info->so_texture)
            free(info->so_texture);
        info->so_texture = path;
    }
    else if (strncmp(line, "WE ", 3) == 0)
    {
        if (info->we_texture)
            free(info->we_texture);
        info->we_texture = path;
    }
    else if (strncmp(line, "EA ", 3) == 0)
    {
        if (info->ea_texture)
            free(info->ea_texture);
        info->ea_texture = path;
    }
    else
    {
        free(path);
        return (ERR_INVALID_FILE);
    }

    return (ERR_NONE);
}