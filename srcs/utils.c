/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:34:41 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/30 15:10:59 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	count_lines(char *path)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

int	check_map_name(char *av)
{
	int		fd;
	char	*first_dot;
	char	*last_dot;

	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	close (fd);
	first_dot = ft_strchr(av, '.');
	last_dot = ft_strrchr(av, '.');
	if (last_dot == NULL || last_dot == av)
		return (1);
	if (first_dot != last_dot)
		return (1);
	if (ft_strncmp(last_dot, ".cub", 4) != 0)
		return (1);
	return (0);
}

int	is_map_start(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == '1' || *line == '0');
}

int	is_texture_or_color(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == 'N' || *line == 'S' || *line == 'W'
		|| *line == 'E' || *line == 'F' || *line == 'C');
}
