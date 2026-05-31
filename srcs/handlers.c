/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 16:24:29 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/31 16:24:50 by kwillian         ###   ########.fr       */
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
