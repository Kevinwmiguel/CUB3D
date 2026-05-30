/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:38:23 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/05 21:23:38 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	is_map_line(char *line)
{
	while (*line == ' ')
		line++;
	return (*line == '1' || *line == '0');
}

int	map_init(char **map, int fd)
{
	char	*line;
	int		i;
	int		map_started;

	i = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started)
		{
			if (is_map_line(line))
				map_started = 1;
			else
			{
				free(line);
				line = get_next_line(fd);
				continue ;
			}
		}
		if (!is_map_line(line))
		{
			free(line);
			break ;
		}
		map[i++] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

char	**get_map(char *path)
{
	int		fd;
	char	**map;
	int		i;
	int		size;

	i = 0;
	size = count_lines(path);
	map = malloc(sizeof(char *) * (size + 1));
	if (!map)
		return (NULL);
	fd = open(path, O_RDONLY);
	i = map_init(map, fd);
	map[i] = NULL;
	close(fd);
	return (map);
}

static void	draw_map_row(t_cub3d *game, int y)
{
	int	screen_x;
	int	screen_y;
	int	x;

	x = 0;
	while (game->map[y][x])
	{
		if (game->map[y][x] == '1')
		{
			screen_x = x * BLOCK - game->player.x + WIDTH / 2;
			screen_y = y * BLOCK - game->player.y + HEIGHT / 2;
			if (screen_x + BLOCK >= 0 && screen_x <= WIDTH
				&& screen_y + BLOCK >= 0 && screen_y <= HEIGHT)
				draw_square(screen_x, screen_y, BLOCK, game);
		}
		x++;
	}
}

void	draw_map(t_cub3d *game)
{
	int	y;

	game->colorhelp = 0xFF00FF;
	y = 0;
	while (game->map[y])
	{
		draw_map_row(game, y);
		y++;
	}
}
