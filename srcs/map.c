/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:38:23 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/31 21:55:05 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static char	*find_map_start(char *line, int fd)
{
	while (line)
	{
		if (is_map_line(line))
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

int	map_init(char **map, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = find_map_start(get_next_line(fd), fd);
	while (line)
	{
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
