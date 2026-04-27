/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:34:41 by kwillian          #+#    #+#             */
/*   Updated: 2026/04/27 23:23:26 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

bool	touch(float px, float py, t_cub3d *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_cub3d *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = game->x2 - game->x1;
	delta_y = game->y2 - game->y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

int	check_map_name(char *av)
{
	int		fd;
	char	*first_dot;
	char	*last_dot;

	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	close (fd);
	first_dot = ft_strchr(av, '.');
	last_dot = ft_strrchr(av, '.');
	if (last_dot == NULL || last_dot == av)
		return (1);
	if (first_dot != last_dot)
		return (1);
	if (ft_strncmp(last_dot, ".cub", 4) != 0)
		return (1);
	return (0);
}
