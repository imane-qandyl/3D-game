/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utills.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:21:02 by imqandyl          #+#    #+#             */
/*   Updated: 2025/05/24 18:23:03 by imqandyl         ###   ########.fr       */
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
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		if (value > 255)
		{
			return (ERR_INVALID_COLOR);
		}
		i++;
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] != ',' && str[i] != '\0')
		return (ERR_INVALID_COLOR);
	*color = value;
	return (ERR_NONE);
}

t_error	validate_color_range(int *target)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!is_valid_color(target[i]))
			return (ERR_INVALID_COLOR);
		i++;
	}
	return (ERR_NONE);
}
