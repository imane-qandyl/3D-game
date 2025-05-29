/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:47:42 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/29 21:15:38 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

static t_error	get_color_target(char *line, t_game *info, int **target)
{
	if (line[0] == 'F')
	{
		if (info->floor_color[0] != -1 || info->floor_color[1] != -1
			|| info->floor_color[2] != -1)
			return (ERR_DUPLICATE_COLOR);
		*target = info->floor_color;
	}
	else if (line[0] == 'C')
	{
		if (info->ceiling_color[0] != -1 || info->ceiling_color[1] != -1
			|| info->ceiling_color[2] != -1)
			return (ERR_DUPLICATE_COLOR);
		*target = info->ceiling_color;
	}
	else
		return (ERR_INVALID_COLOR);
	return (ERR_NONE);
}

static t_error	parse_color_values(char *ptr, int *target)
{
	t_error	err;
	int		i;

	i = 0;
	while (i < 3)
	{
		err = parse_color_value(ptr, &target[i]);
		if (err != ERR_NONE)
			return (err);
		while (*ptr && *ptr != ',')
			ptr++;
		if (i < 2)
		{
			if (!*ptr)
				return (ERR_INVALID_COLOR);
			ptr++;
		}
		i++;
	}
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (*ptr != '\0')
		return (ERR_INVALID_COLOR);
	return (validate_color_range(target));
}

t_error	parse_colors(char *line, t_game *info)
{
	char	*ptr;
	int		*target;
	t_error	err;

	if (!line || !info)
		return (ERR_INVALID_COLOR);
	err = get_color_target(line, info, &target);
	if (err != ERR_NONE)
		return (err);
	ptr = line + 1;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	return (parse_color_values(ptr, target));
}
