/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:25:06 by lalwafi           #+#    #+#             */
/*   Updated: 2024/01/13 17:30:06 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ---------------------------------------------------- my function
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// ---------------------------------------------------- main function
// #include <string.h>
// int	main(void)
// {
// 	char	*src = "helloooooo";
// 	char	dst[200];

// 	printf("%zu\n", ft_strlcpy(dst, src, 5));
// 	printf("%zu\n", strlcpy(dst, src, 5));
// }