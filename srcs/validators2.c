/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:32:04 by kwillian          #+#    #+#             */
/*   Updated: 2026/02/14 14:32:24 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	check_first_last_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' '
			&& line[i] != '\t' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

static int	check_middle_lines(t_cub3d *game, char **map)
{
	int	line;
	int	i;

	line = 1;
	while (map[line + 1])
	{
		i = 0;
		while (map[line][i])
		{
			if (map[line][i] == '0')
			{
				if (!check_englobe(map[line],
						map[line - 1], map[line + 1]))
				{
					printf("Some element is wrong!\n");
					destroy_game(game);
				}
			}
			i++;
		}
		line++;
	}
	return (1);
}

bool	validate_map(t_cub3d *game, char **map)
{
	int	last;

	if (!check_first_last_line(map[0]))
		return (0);
	if (!check_middle_lines(game, map))
		return (0);
	last = 0;
	while (map[last])
		last++;
	if (!check_first_last_line(map[last - 1]))
		return (0);
	return (1);
}
