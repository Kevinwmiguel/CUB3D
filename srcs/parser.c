/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:34:41 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/30 15:24:23 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	handle_color_line(char *line, int *f, int *c)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (line[0] == 'F')
	{
		if (line[1] != ' ' || !check_rgb_format(line) || *f)
			return (0);
		*f = 1;
	}
	else if (line[0] == 'C')
	{
		if (line[1] != ' ' || !check_rgb_format(line) || *c)
			return (0);
		*c = 1;
	}
	return (1);
}

int	validate_config_line(char *line, int *f, int *c)
{
	if (is_empty_line(line))
		return (1);
	if (is_map_start(line))
		return (2);
	if (!is_texture_or_color(line))
		return (0);
	if (!handle_color_line(line, f, c))
		return (0);
	return (1);
}

static int	process_file_lines(int fd, int *f, int *c)
{
	char	*line;
	int		status;
	int		map_started;
	int		map_ended;

	map_started = 0;
	map_ended = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (map_started)
		{
			if (is_map_start(line) && !map_ended)
			{
				free(line);
				line = get_next_line(fd);
				continue ;
			}
			if (is_empty_line(line))
			{
				map_ended = 1;
				free(line);
				line = get_next_line(fd);
				continue ;
			}
			if (is_texture_or_color(line))
			{
				if (!handle_color_line(line, f, c))
					return (free(line), 0);
				map_ended = 1;
				free(line);
				line = get_next_line(fd);
				continue ;
			}
			return (free(line), 0);
		}
		status = validate_config_line(line, f, c);
		if (status == 0)
			return (free(line), 0);
		if (status == 2)
			map_started = 1;
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	precheck_colors(char *path)
{
	int		fd;
	int		f;
	int		c;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	f = 0;
	c = 0;
	if (!process_file_lines(fd, &f, &c))
		return (close(fd), 0);
	close(fd);
	return (f && c);
}
