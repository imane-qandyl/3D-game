/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 19:15:08 by lalwafi           #+#    #+#             */
/*   Updated: 2024/01/12 19:31:48 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

// #include <string.h>
// int	main(void)
// {
// 	char	a[] = "aaaaaa";
// 	char	b[10];
// 	char	d[10];
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
// 	i = 0;
// 	printf("%s", c);
// 	while (d[i] != '\0')
// 	{
// 		printf("%c", d[i]);
// 		i++;
// 	}
// 	printf("%s", c);
// 	ft_memcpy(b, a, sizeof(char) * 10);
// 	memcpy(d, a, sizeof(char) * 10);
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
