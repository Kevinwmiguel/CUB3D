/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:52:14 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/30 15:10:59 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	parse_rgb_component(char **s)
{
	char	*start;
	int		value;

	if (**s < '0' || **s > '9')
		return (-1);
	start = *s;
	while (**s >= '0' && **s <= '9')
		(*s)++;
	if (*s - start > 3)
		return (-1);
	value = ft_atoi(start);
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

static char	*build_rgb_hex(int r, int g, int b)
{
	char	*red;
	char	*green;
	char	*blue;
	char	*tmp;
	char	*final;

	red = ft_int_to_hex(r);
	green = ft_int_to_hex(g);
	blue = ft_int_to_hex(b);
	tmp = ft_strjoin(red, green);
	final = ft_strjoin(tmp, blue);
	free(red);
	free(green);
	free(blue);
	free(tmp);
	return (final);
}

char	*process_rgb_line(char *line, t_cub3d *game)
{
	char	*s;
	int		rgb[3];
	int		i;

	(void)game;
	s = line + 1;
	while (*s == ' ' || *s == '\t')
		s++;
	i = 0;
	while (i < 3)
	{
		rgb[i] = parse_rgb_component(&s);
		if (rgb[i] < 0)
			return (NULL);
		i++;
		while (*s == ' ' || *s == '\t')
			s++;
		if (i == 3)
			break ;
		if (*s != ',')
			return (NULL);
		s++;
		while (*s == ' ' || *s == '\t')
			s++;
	}
	while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r')
		s++;
	if (*s != '\0')
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
