/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:16:13 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/05 21:23:43 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

void	calculate_map_dimensions(t_cub3d *game)
{
	int	y;
	int	max_x;

	y = 0;
	game->x_map = 0;
	while (game->map[y])
	{
		max_x = 0;
		while (game->map[y][max_x])
			max_x++;
		if (max_x > game->x_map)
			game->x_map = max_x;
		y++;
	}
	game->y_map = y;
}
