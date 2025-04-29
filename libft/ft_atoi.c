/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:39:17 by imqandyl          #+#    #+#             */
/*   Updated: 2024/07/06 08:31:39 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_sign(int *i, const char *str, int *sign)
{
	while (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	while (str[*i] == '0')
		(*i)++;
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	res;
	int					sign;
	int					digit;

	i = 0;
	res = 0;
	digit = 0;
	sign = 1;
	check_sign(&i, str, &sign);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
		digit++;
		if (((res > LONG_MAX) && (sign > 0))
			|| (((digit > 19) && (sign > 0))))
			return (-1);
		else if ((res > (LONG_MAX) && (sign < 0))
			|| (((digit > 19) && (sign < 0))))
			return (0);
	}
	return (sign * res);
}
