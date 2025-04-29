/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:51:01 by lalwafi           #+#    #+#             */
/*   Updated: 2024/01/17 20:16:32 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h> 

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	const char	*a = "Hello everybody";
// 	int	c = 'r';
// 	printf("%s\n", ft_strchr(a, c));
// 	printf("%s\n", strchr(a, c));
// }
