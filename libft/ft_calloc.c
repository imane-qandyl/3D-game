/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:47:38 by lalwafi           #+#    #+#             */
/*   Updated: 2024/01/16 21:22:09 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*a;

	if (count && size && ((count * size) > 214743648))
		return (NULL);
	a = malloc(size * count);
	if (a == NULL)
		return (NULL);
	ft_bzero(a, (size * count));
	return (a);
}

// int	main(void)
// {
// 	void *str = ft_calloc(0, 0);

// 	if (str == ((void *)0))
// 		printf("%s", "failed");
// 	else
// 		printf("%s", "yesssss");
// 	free(str);
// }