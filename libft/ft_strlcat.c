/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:54:05 by lalwafi           #+#    #+#             */
/*   Updated: 2024/01/13 18:49:02 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	i = 0;
	if (size <= dstlen)
		return (srclen + size);
	while (src[i] != '\0' && i < (size - dstlen - 1))
	{
		dst[i + dstlen] = src[i];
		i++;
	}
	dst[i + dstlen] = '\0';
	return (srclen + dstlen);
}

// ---------------------------------------------------- main function
// #include <string.h>
// int	main(void)
// {
// 	// char	*src = "world!";
// 	// char	*dst = "hello ";

// 	printf("%zu\n", ft_strlcat("pqrs", "abcdefghi", 10));
// 	printf("%zu\n", strlcat("pqrs", "abcdefghi", 10));
// 	// printf("%s\n", dst);
// }
