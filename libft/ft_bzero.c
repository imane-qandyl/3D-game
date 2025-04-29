/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:11:37 by lalwafi           #+#    #+#             */
/*   Updated: 2024/01/12 12:22:22 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (n > i)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

// int	main(void)
// {
// 	char	a[5] = "12345";
// 	char	z[] = "+=";
// 	printf("%s\n", z);
// 	printf("%c\n", a[0]);
// 	printf("%c\n", a[1]);
// 	printf("%c\n", a[2]);
// 	printf("%c\n", a[3]);
// 	printf("%c\n", a[4]);
// 	printf("%s\n", z);
// 	bzero(a, sizeof(char) * 5);
// 	printf("%s\n", z);
// 	printf("%c\n", a[0]);
// 	printf("%c\n", a[1]);
// 	printf("%c\n", a[2]);
// 	printf("%c\n", a[3]);
// 	printf("%c\n", a[4]);
// 	printf("%s\n", z);
// }