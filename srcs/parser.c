/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:34:41 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/31 21:42:46 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	print_map_last_error(void)
{
	ft_putstr_fd("Error\nMap is not the last element\n", 2);
	return (-1);
}

static int	handle_map_lines(char *line, int *map_ended)
{
	if (is_map_start(line) && !(*map_ended))
		return (1);
	if (is_empty_line(line))
	{
		*map_ended = 1;
		return (1);
	}
	return (0);
}

static int	process_config_line(char *line, int *f,
	int *c, int *map_started)
{
	int	status;

	status = validate_config_line(line, f, c);
	if (status == 0)
		return (0);
	if (status == 2)
		*map_started = 1;
	return (1);
}

static int	process_file_lines(int fd, int *f, int *c)
{
	char	*line;
	int		map_started;
	int		map_ended;

	map_started = 0;
	map_ended = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (map_started && !handle_map_lines(line, &map_ended))
			return (free(line), print_map_last_error());
		if (!map_started
			&& !process_config_line(line, f, c, &map_started))
			return (free(line), 0);
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
	int		status;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	f = 0;
	c = 0;
	status = process_file_lines(fd, &f, &c);
	if (status != 1)
		return (close(fd), status);
	close(fd);
	return (f && c);
}
