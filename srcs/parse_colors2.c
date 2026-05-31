/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:46:04 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/31 21:55:10 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	is_map_line(char *line)
{
	while (*line == ' ')
		line++;
	return (*line == '1' || *line == '0');
}

int	parse_rgb_component(char **s)
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

char	*build_rgb_hex(int r, int g, int b)
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
