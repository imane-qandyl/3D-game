/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:47:42 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/08 15:38:51 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_color(int value)
{
	return (value >= 0 && value <= 255);
}

t_error	parse_color_value(const char *str, int *color)
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
		{
			//printf("bruh\n");
			return (ERR_INVALID_COLOR);
		}
		i++;
	}
	// Skip trailing whitespace
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	// Check if we have any non-whitespace characters left
	if (str[i] && str[i] != ','&& str[i] != '\0')
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

	if (!line || !info || (line[0] != 'F' && line[0] != 'C')) {
		return (ERR_INVALID_COLOR);
	}
		if (line[0] == 'F')
	{
		if (info->floor_color[0] != -1 || info->floor_color[1] != -1 || info->floor_color[2] != -1)
			return (ERR_DUPLICATE_COLOR);
	target = info->floor_color;
	}
	else if (line[0] == 'C')
	{
		if (info->ceiling_color[0] != -1 || info->ceiling_color[1] != -1 || info->ceiling_color[2] != -1)
			return (ERR_DUPLICATE_COLOR);
	target = info->ceiling_color;
	}	
	else {
		return (ERR_INVALID_COLOR);
	}
		// Skip identifier and whitespace
	ptr = line + 1;
	while (*ptr && (*ptr == ' ' || *ptr == '\t'))
		ptr++;
	// Parse each color component
	while(i < 3) //rgb
	{
		// printf("%s\n",ptr);
		if ((err = parse_color_value(ptr, &target[i])) != ERR_NONE) {
			printf("Hello");
			return (err);		
		}
	// Skip to next component
		while (*ptr && *ptr != ',')
		ptr++;
		if (i < 2) //move past the comma
		{
			if (!*ptr)
				return (ERR_INVALID_COLOR);
			ptr++;
		}
		i++;
	}
	//After parsing 3 colors, check if anything else left
	while (*ptr == ' ' || *ptr == '\t')
		ptr++; // skip any trailing spaces

	if (*ptr != '\0')
		return (ERR_INVALID_COLOR); // Unexpected garbage after colors
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
