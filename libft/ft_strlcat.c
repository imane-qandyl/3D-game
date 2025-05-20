/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:34:21 by imqandyl          #+#    #+#             */
/*   Updated: 2024/07/06 08:32:38 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;
	size_t	j;

	lensrc = ft_strlen(src);
	i = 0;
	j = 0;
	if (dstsize == 0)
		return (lensrc);
	while (dst[i] && i < dstsize)
		i++;
	lendst = i;
	while (src[j] && i < dstsize - 1)
	{
		dst[i] = src[i - lendst];
		i++;
		j++;
	}
	if (lendst < dstsize)
		dst[i] = '\0';
	return (lendst + lensrc);
}
