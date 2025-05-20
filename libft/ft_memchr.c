/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:32:38 by imqandyl          #+#    #+#             */
/*   Updated: 2024/07/03 12:27:46 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*src;
	unsigned char		car;

	i = 0;
	src = s;
	car = c;
	while (i < n)
	{
		if (src[i] == car)
		{
			return ((void *)(src + i));
		}
		i++;
	}
	return (NULL);
}
