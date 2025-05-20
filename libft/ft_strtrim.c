/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:35:01 by imqandyl          #+#    #+#             */
/*   Updated: 2024/07/03 11:35:01 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size_s1;

	if (s1 == NULL || set == NULL)
		return (ft_strdup(""));
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	size_s1 = ft_strlen(s1);
	while (ft_strchr(set, s1[size_s1 - 1]) && size_s1 != 0)
		size_s1--;
	return (ft_substr(s1, 0, size_s1));
}
