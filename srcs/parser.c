/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:34:41 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/18 21:11:46 by made-jes         ###   ########.fr       */
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

	line = get_next_line(fd);
	while (line)
	{
		status = validate_config_line(line, f, c);
		if (status == 0)
			return (free(line), 0);
		if (status == 2)
		{
			free(line);
			break ;
		}
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
