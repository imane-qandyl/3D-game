/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:23:47 by lalwafi           #+#    #+#             */
/*   Updated: 2024/01/19 19:10:30 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strdup(const char *s1)
// {
// 	size_t	i;
// 	char	*copy;

// 	i = 0;
// 	copy = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
// 	if (!copy)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		copy[i] = s1[i];
// 		i++;
// 	}
// 	copy[i] = '\0';
// 	return (copy);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*substring;
// 	size_t	i;
// 	size_t	slen;

// 	i = 0;
// 	slen = ft_strlen(s) + 1;
// 	if (start > slen || !s || !len)
// 		return (ft_strdup(""));
// 	if (len > (slen - start))
// 		len = slen - start;
// 	substring = (char *)malloc((len + 1) * sizeof(char));
// 	if (!substring)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		substring[i] = s[start + i];
// 		i++;
// 	}
// 	substring[i] = '\0';
// 	return (substring);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	while (*s != (char)c)
// 	{
// 		if (*s == '\0')
// 			return (NULL);
// 		s++;
// 	}
// 	return ((char *)s);
// }

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;

	if (s1[0] == '\0')
		return (ft_strdup(""));
	if (set[0] == '\0')
		return (ft_strdup(s1));
	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i] != '\0')
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) && i > 0)
		i--;
	return (ft_substr(s1, start, (i - start + 1)));
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*a = "jfbgvg jhvh bfv";
// 	char	*b = " ";
// 	printf("#%s#\n", ft_strtrim(a, b));
// }