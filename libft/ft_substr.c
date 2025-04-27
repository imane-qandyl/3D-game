/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:35:07 by imqandyl          #+#    #+#             */
/*   Updated: 2024/07/03 11:35:07 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*array;
	size_t	i;
	size_t	str_len;

	i = 0;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start > str_len)
		len = 0;
	if (len > str_len - start)
	{
		len = str_len - start;
	}
	array = (char *)malloc(len + 1);
	if (!array)
		return (NULL);
	while (start < str_len && i < len)
	{
		array[i] = s[start];
		start++;
		i++;
	}
	array[i] = '\0';
	return (array);
}
