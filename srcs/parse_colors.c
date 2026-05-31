/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:52:14 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/31 21:54:24 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	parse_rgb_values(char **s, int rgb[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		rgb[i] = parse_rgb_component(s);
		if (rgb[i] < 0)
			return (0);
		i++;
		while (**s == ' ' || **s == '\t')
			(*s)++;
		if (i == 3)
			break ;
		if (**s != ',')
			return (0);
		(*s)++;
		while (**s == ' ' || **s == '\t')
			(*s)++;
	}
	return (1);
}

static int	check_rgb_end(char *s)
{
	while (*s == ' ' || *s == '\t'
		|| *s == '\n' || *s == '\r')
		s++;
	return (*s == '\0');
}

char	*process_rgb_line(char *line, t_cub3d *game)
{
	char	*s;
	int		rgb[3];

	(void)game;
	s = line + 1;
	while (*s == ' ' || *s == '\t')
		s++;
	if (!parse_rgb_values(&s, rgb))
		return (NULL);
	if (!check_rgb_end(s))
		return (NULL);
	return (build_rgb_hex(rgb[0], rgb[1], rgb[2]));
}

static void	process_line(t_cub3d *game, char *line)
{
	char	*trim;

	trim = line;
	while (*trim == ' ' || *trim == '\t')
		trim++;
	if (trim[0] == 'F' && trim[1] == ' ')
	{
		if (game->floor)
			free(game->floor);
		game->floor = process_rgb_line(trim, game);
	}
	else if (trim[0] == 'C' && trim[1] == ' ')
	{
		if (game->ceiling)
			free(game->ceiling);
		game->ceiling = process_rgb_line(trim, game);
	}
}

void	parse_colors(t_cub3d *game, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		process_line(game, line);
		free(line);
		if (game->floor && game->ceiling)
			break ;
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
