/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:37:12 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/13 23:38:15 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

bool	validate_map(char **map);

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

bool	validate_map(char **map)
{
	int	x;
	int	y;
	int	count_zero;
	int	count_player;

	count_zero = 0;
	count_player = 0;

	if (!map || !map[0])
		return (false);

	/* topo */
	for (x = 0; map[0][x]; x++)
		if (map[0][x] != '1' && map[0][x] != ' ')
			return (false);

	for (y = 0; map[y]; y++)
	{
		for (x = 0; map[y][x]; x++)
		{
			if (!is_map_char(map[y][x]) && map[y][x] != ' ')
				return (false);

			if (map[y][x] == '0')
				count_zero++;

			if (is_player_char(map[y][x]))
				count_player++;

			if (map[y][x] == '0' || is_player_char(map[y][x]))
				if (is_open_to_void(map, y, x))
					return (false);
		}

		/* laterais */
		if (map[y][0] != '1' && map[y][0] != ' ')
			return (false);
		if (map[y][ft_strlen(map[y]) - 1] != '1'
			&& map[y][ft_strlen(map[y]) - 1] != ' ')
			return (false);
	}

	/* fundo */
	for (x = 0; map[y - 1][x]; x++)
		if (map[y - 1][x] != '1' && map[y - 1][x] != ' ')
			return (false);

	if (count_zero < 4)
		return (false);

	if (count_player != 1)
		return (false);

	return (true);
}
