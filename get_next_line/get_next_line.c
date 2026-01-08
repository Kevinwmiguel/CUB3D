/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:25:24 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/08 00:33:12 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			flag;
	int			read_l;

	line = NULL;
	if (fd < 0 || fd >= FOPEN_MAX)
		return (buffer_full_clear(fd, (char **)buffer, line));
	while (1)
	{
		if (buffer[0] == '\0')
		{
			read_l = read(fd, buffer, BUFFER_SIZE);
			if (read_l == -1)
				return (buffer_full_clear(fd, NULL, line));
			if (read_l == 0)
				return (line);
		}
		flag = next_line(&line, buffer);
		buffer_clear(buffer);
		if (flag == 1)
			return (line);
		if (flag == -1)
			return (NULL);
	}
}

/*
int	main(void)
{
	char *line;
	int fd;

	fd = open("texto1", O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line: %s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
