/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:37:12 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/21 00:24:23 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

bool	is_map_char(char c)
{
	return (c == '0' || c == '1'
		|| c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_open_to_void(char **map, int y, int x)
{
	if (y == 0 || x == 0)
		return (true);
	if (!map[y + 1] || !map[y][x + 1])
		return (true);

	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
		|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (true);

	return (false);
}

size_t calc_line(char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

check_englobe(char *current, char *prev, char *next)
{
	int i = 0;
	while ()
}

bool	validate_map(char **map)
{
	int	i;
	int size;
	int line;

	line = 0;
	size = 0;
	i = 0;
	//first line
	while (map[0][i])
	{
		if (map[0][i] != '1' && (map[0][i] != ' ' && map[0][i] != '\t' && map[0][i] != '\r'))
			return (0);
		i++;
	}
	line = 1;
	//middle line
	i = 0;
	while (map[line])
	{
		if (map[line][i] == '0' && map[line - 1] && map[line + 1])
			check_englobe(map[line], map[line -1], map[line + 1]);
		size = calc_line(map[line]);
		if (map[line][0] != '1' && map[line][0] != ' ' && map[line][0] != '\t')
			return (0);
		if (map[line][size - 1] != '1' && map[line][size - 1] != ' ' && map[line][size - 1] != '\t')
			return (0);
		line++;
		i++;
	}
	//end line
	i = 0;
	line = line - 1;
	while (map[line][i])
	{
		if (map[line][0] != '1' && map[line][0] != ' ' && map[line][0] != '\t')
			return (0);
		i++;
	}
	return (1);
}