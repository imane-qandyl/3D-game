/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:31:45 by imqandyl          #+#    #+#             */
/*   Updated: 2024/07/03 12:54:08 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int nb)
{
	size_t	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	length;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	length = ft_intlen(n);
	str = malloc(length + 1);
	if (!str)
		return (NULL);
	str[length] = '\0';
	if (n == 0)
		return (free(str), ft_strdup("0"));
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n)
	{
		str[--length] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}
