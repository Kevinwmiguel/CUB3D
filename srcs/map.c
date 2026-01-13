/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:38:23 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/13 23:29:21 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	is_map_line(char *line)
{
	while (*line == ' ')
		line++;
	return (*line == '1' || *line == '0');
}

int	map_init(char *line, char **map, int map_started, int fd)
{
	int i;

	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (!map_started)
		{
			if (is_map_line(line))
				map_started = 1;
			else
			{
				free(line);
				continue ;
			}
		}
		map[i++] = ft_strtrim(line, "\n");
		free(line);
	}
	return (i);
}

char	**get_map(char *path)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;
	int		map_started;

	i = 0;
	map_started = 0;
	line = NULL;
	map = malloc(sizeof(char *) * 100);
	fd = open(path, O_RDONLY);
	i = map_init(line, map, map_started, fd);
	map[i] = NULL;
	close(fd);
	return (map);
}

void	draw_map(t_cub3d *game)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;
	int	color;

	color = 0xFF00FF;
	for (y = 0; game->map[y]; y++)
	{
		for (x = 0; game->map[y][x]; x++)
		{
			if (game->map[y][x] == '1')
			{
				screen_x = x * BLOCK - game->player.x + WIDTH / 2;
				screen_y = y * BLOCK - game->player.y + HEIGHT / 2;
				if (screen_x + BLOCK < 0 || screen_x > WIDTH)
					continue ;
				if (screen_y + BLOCK < 0 || screen_y > HEIGHT)
					continue ;
				draw_square(screen_x, screen_y, BLOCK, color, game);
			}
		}
	}
}
