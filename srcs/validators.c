/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:37:12 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/18 16:12:58 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

bool	is_open_to_void(char **map, int y, int x)
{
	if (y == 0 || x == 0)
		return (true);
	if (!map[y + 1] || !map[y][x + 1])
		return (true);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || map[y][x - 1] == ' '
		|| map[y][x + 1] == ' ')
		return (true);
	return (false);
}

size_t	calc_line(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	check_englobe(char *cur, char *prev, char *next)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cur);
	while (i < len)
	{
		if (is_walkable(cur[i]))
		{
			if (i == 0 || i == len - 1)
				return (0);
			if (cur[i - 1] == ' ' || cur[i + 1] == ' ')
				return (0);
			if (!prev || i >= (int)ft_strlen(prev)
				|| prev[i] == ' ')
				return (0);
			if (!next || i >= (int)ft_strlen(next)
				|| next[i] == ' ')
				return (0);
		}
		i++;
	}
	return (1);
}
