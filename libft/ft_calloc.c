/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:31:13 by imqandyl          #+#    #+#             */
/*   Updated: 2024/07/04 19:36:18 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;

	if (size && count > 0 && count > SIZE_MAX / size)
		return (NULL);
	array = malloc(count * size);
	if (!array)
		return (NULL);
	ft_bzero(array, count * size);
	return (array);
}
