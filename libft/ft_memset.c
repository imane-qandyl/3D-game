/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 17:32:52 by lalwafi           #+#    #+#             */
/*   Updated: 2024/01/12 19:35:07 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	if (!b && !len)
		return (NULL);
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}

// int	main(void)
// {
// 	char	a[10];
// 	printf("%s\n", a);
// 	printf("%s\n", memset(a, 'c', sizeof(char) * 10));
// 	printf("%s\n", a);
// 	printf("%s\n", ft_memset(a, 'd', sizeof(char) * 10));
// 	printf("%s\n", a);
// }
