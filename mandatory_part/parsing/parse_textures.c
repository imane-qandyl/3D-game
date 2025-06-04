/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:48:11 by imqandyl          #+#    #+#             */
/*   Updated: 2025/06/05 01:13:11 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_texture_file(const char *path)
{
	FILE	*file;

	if (!path)
		return (0);
	file = fopen(path, "r");
	if (!file)
		return (0);
	fclose(file);
	return (1);
}

char	*extract_path(const char *line)
{
	char	*path;
	int		i;
	int		start;

	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	path = (char *)malloc(sizeof(char) * (i - start + 1));
	if (!path)
		return (NULL);
	strncpy(path, line + start, i - start);
	path[i - start] = '\0';
	return (path);
}

static t_error	assign_texture(char **target, char *path)
{
	if (*target)
	{
		free(path);
		return (ERR_DUPLICATE_TEXTURE);
	}
	*target = path;
	return (ERR_NONE);
}

t_error	parse_textures(char *line, t_game *info)
{
	char	*path;

	path = extract_path(line);
	if (!path || !validate_texture_file(path))
	{
		free(path);
		return (ERR_MISSING_TEXTURE);
	}
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (assign_texture(&info->no_texture, path));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (assign_texture(&info->so_texture, path));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (assign_texture(&info->we_texture, path));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (assign_texture(&info->ea_texture, path));
	else
	{
		free(path);
		return (ERR_MISSING_TEXTURE);
	}
	return (ERR_MISSING_TEXTURE);
}
