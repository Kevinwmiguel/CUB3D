/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:32:04 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/18 16:26:55 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	check_map_gaps(char **map)
{
	int	i;
	int	in_map;

	i = 0;
	in_map = 0;
	while (map[i])
	{
		if (is_empty_line(map[i]))
		{
			if (in_map)
			{
				while (map[i] && is_empty_line(map[i]))
					i++;
				if (map[i])
					return (0);
			}
		}
		else
			in_map = 1;
		i++;
	}
	return (1);
}

static int	check_first_last_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
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
			if (map[line][i] == '0' || map[line][i] == 'N'
				|| map[line][i] == 'S' || map[line][i] == 'E'
				|| map[line][i] == 'W')
			{
				if (!check_englobe(map[line],
						map[line - 1], map[line + 1]))
				{
					printf("Error\nMap not closed!\n");
					destroy_game(game, 1);
				}
			}
			i++;
		}
		line++;
	}
	return (1);
}

int	check_elements(char **map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				player++;
			else if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	if (player != 1)
		return (0);
	return (1);
}

bool	validate_map(t_cub3d *game, char **map)
{
	int	last;

	if (!check_map_gaps(map))
		return (0);
	if (!check_first_last_line(map[0]))
		return (0);
	if (!check_elements(map))
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
