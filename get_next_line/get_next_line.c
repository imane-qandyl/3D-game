/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:25:24 by lalwafi           #+#    #+#             */
/*   Updated: 2025/04/29 09:07:22 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_save(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!new_buffer)
		return (NULL);
	while (buffer[++i])
		new_buffer[j++] = buffer[i];
	new_buffer[j] = 0;
	free(buffer);
	return (new_buffer);
}

char	*ft_thing_to_print(char *buffer)
{
	char	*thing_to_print;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	thing_to_print = (char *)malloc(sizeof(char) * (i + 1 + (buffer[i] == '\n')));
	if (!thing_to_print)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		thing_to_print[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		thing_to_print[i++] = '\n';
	thing_to_print[i] = '\0';
	return (thing_to_print);
}

char	*ft_read_it(char *buffer, int fd)
{
	int		read_return;
	char	*line;

	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	read_return = 1;
	while (read_return != 0 && ft_strchr(buffer, '\n') == 0)
	{
		read_return = read(fd, line, BUFFER_SIZE);
		if (read_return == -1)
		{
			if (buffer != NULL)
				free(buffer);
			free(line);
			return (NULL);
		}
		line[read_return] = '\0';
		buffer = ft_strjoin(buffer, line);
	}
	free(line);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*thing_to_print;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (!buffer)
		buffer = NULL;
	buffer = ft_read_it(buffer, fd);
	if (!buffer)
		return (NULL);
	thing_to_print = ft_thing_to_print(buffer);
	buffer = ft_save(buffer);
	return (thing_to_print);
}

// #include <fcntl.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		number;

// 	number = 0;
// 	fd = open("idk.txt", O_RDONLY);
// 	if (fd == -1)
// 		printf("lmao nah -1");
// 	while ((line = get_next_line(fd)))
// 		printf("%s", line);
// 	close(fd);
// }
