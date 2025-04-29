/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:00:47 by lalwafi           #+#    #+#             */
/*   Updated: 2024/01/12 20:43:48 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!src && !dst)
		return (NULL);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		i = len;
		while (0 < i)
		{
			i--;
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		}
	}
	return (dst);
}

// #include <string.h>
// int	main(void)
// {
// 	char	a[] = "1hello23456789";
// 	char	b[15];
// 	char	d[15];
// 	char	c[2] = "\n";
// 	int i = 0;
// 	while (a[i] != '\0')
// 	{
// 		printf("%c", a[i]);
// 		i++;
// 	}
// 	printf("%s", c);
// 	i = 0;
// 	while (b[i] != '\0')
// 	{
// 		printf("%c", b[i]);
// 		i++;
// 	}
// 	printf("%s", c);
// 	i = 0;
// 	while (d[i] != '\0')
// 	{
// 		printf("%c", d[i]);
// 		i++;
// 	}
// 	printf("%s", c);
// 	ft_memmove(b, a, 15);
// 	memmove(d, a, 15);
// 	printf("%s", c);
// 	i = 0;
// 	while (a[i] != '\0')
// 	{
// 		printf("%c", a[i]);
// 		i++;
// 	}
// 	printf("%s", c);
// 	i = 0;
// 	while (b[i] != '\0')
// 	{
// 		printf("%c", b[i]);
// 		i++;
// 	}
// 	printf("%s", c);
// 	i = 0;
// 	while (d[i] != '\0')
// 	{
// 		printf("%c", d[i]);
// 		i++;
// 	}
// 	printf("%s", c);
// }
