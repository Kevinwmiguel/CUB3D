/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:38:23 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/26 13:13:11 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	is_map_line(char *line)
{
	while (*line == ' ')
		line++;
	return (*line == '1' || *line == '0');
}

int map_init(char **map, int fd)
{
    char *line;
    int i = 0;
    int map_started = 0;

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
                continue;
            }
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

	i = 0;
	map = malloc(sizeof(char *) * 100);
	fd = open(path, O_RDONLY);
	i = map_init(map, fd);
	map[i] = NULL;
	close(fd);
	return (map);
}

void	draw_map(t_cub3d *game)
{
	int	screen_x;
	int	screen_y;
	int	color;

	color = 0xFF00FF;
	game->y_map = 0;
	while (game->map[game->y_map][game->x_map])
	{
		game->x_map = 0;
		while (game->map[game->y_map][game->x_map])
		{
			if (game->map[game->y_map][game->x_map] == '1')
			{
				screen_x = game->x_map * BLOCK - game->player.x + WIDTH / 2;
				screen_y = game->y_map * BLOCK - game->player.y + HEIGHT / 2;
				if (screen_x + BLOCK < 0 || screen_x > WIDTH)
					continue ;
				if (screen_y + BLOCK < 0 || screen_y > HEIGHT)
					continue ;
				draw_square(screen_x, screen_y, BLOCK, color, game);
			}
			game->x_map++;
		}
		game->y_map++;
	}
}

bool	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}
