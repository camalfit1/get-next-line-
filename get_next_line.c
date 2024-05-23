/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camalfit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:38:51 by camalfit          #+#    #+#             */
/*   Updated: 2024/03/29 16:19:18 by camalfit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*newline(char *join)
{
	int		c;
	char	*str;

	c = 0;
	if (!join[c])
		return (NULL);
	while (join[c] && join[c] != '\n')
		c++;
	str = (char *)malloc(sizeof(char) * (c + 2));
	if (!str)
		return (NULL);
	c = 0;
	while (join[c] && join[c] != '\n')
	{
		str[c] = join[c];
		c++;
	}
	if (join[c] == '\n')
	{
		str[c] = join[c];
		c++;
	}
	str[c] = '\0';
	return (str);
}

char	*group(char *join)
{
	int		c;
	int		begin;
	char	*str;

	c = 0;
	while (join[c] && join[c] != '\n')
		c++;
	if (!join[c])
	{
		free(join);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(join) - c + 1));
	if (!str)
	{
		free(join);
		return (NULL);
	}
	c++;
	begin = 0;
	while (join[c])
		str[begin++] = join[c++];
	str[begin] = '\0';
	free(join);
	return (str);
}

char	*readtext(int fd, char *join)
{
	char	*buffer;
	int		countcar;

	buffer = malloc (sizeof(char) * (BUFFER_SIZE +1));
	if (!buffer)
		return (0);
	countcar = 1;
	while (!ft_strchr(join, '\n') && countcar != 0)
	{
		countcar = read (fd, buffer, BUFFER_SIZE);
		if (countcar < 0)
		{
			free(buffer);
			return (0);
		}
		buffer[countcar] = '\0';
		join = ft_strjoin(join, buffer);
	}
	free(buffer);
	return (join);
}

char	*get_next_line(int fd)
{
	char		*new;
	static char	*join;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	join = readtext(fd, join);
	if (!join)
		return (NULL);
	new = newline(join);
	join = group(join);
	return (new);
}
/*
#include <stdio.h> // enlever a l'envoie, juste pour test
#include <fcntl.h> // pareil
#include <string.h>

int	main(void)
{
	char	*line;
	int	fd = open("test.txt", O_RDONLY);
	if (fd == 0)
		return (1);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
        printf("%s", line);

	printf("\n");
	close(fd);
	return (0);
} */
