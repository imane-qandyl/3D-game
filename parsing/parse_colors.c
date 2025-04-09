/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:47:42 by imqandyl          #+#    #+#             */
/*   Updated: 2025/04/09 20:00:36 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_valid_color(int value)
{
	return (value >= 0 && value <= 255);
}

static t_error	parse_color_value(const char *str, int *color)
{
	int	value;
	int	i;

	i = 0;
	value = 0;
	// Skip leading whitespace
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	// Parse number
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		if (value > 255)
			return (ERR_INVALID_COLOR);
		i++;
	}
	// Skip trailing whitespace
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	// Check if we have any non-whitespace characters left
	if (str[i] && str[i] != ',' && str[i] != '\n')
		return (ERR_INVALID_COLOR);
	*color = value;
	return (ERR_NONE);
}

t_error	parse_colors(char *line, t_game *info)
{
	int *target;
	char *ptr;
	t_error err;
	int i;
	i = 0;

	if (!line || !info || (line[0] != 'F' && line[0] != 'C'))
		return (ERR_INVALID_COLOR);
	target = (line[0] == 'F') ? info->floor_color : info->ceiling_color;
	// Skip identifier and whitespace
	ptr = line + 1;
	while (*ptr && (*ptr == ' ' || *ptr == '\t'))
		ptr++;
	// Parse each color component
	while(i < 3)
	{
		if ((err = parse_color_value(ptr, &target[i])) != ERR_NONE)
			return (err);
		// Skip to next component
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
	i = 0;
	// Validate final values
	while(i < 3)
	{
		if (!is_valid_color(target[i]))
			return (ERR_INVALID_COLOR);
		i++;
	}
	return (ERR_NONE);
}
