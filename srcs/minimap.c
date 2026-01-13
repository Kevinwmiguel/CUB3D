/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:28:52 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/13 23:30:08 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	draw_minimap_border(t_cub3d *game)
{
	int	x;
	int	y;
	int	left;
	int	top;

	left = WIDTH - MINIMAP_SIZE - MINIMAP_MARGIN;
	top = HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN;
	for (x = 0; x < MINIMAP_SIZE; x++)
	{
		put_pixel(left + x, top, 0x000000, game);
		put_pixel(left + x, top + MINIMAP_SIZE, 0x000000, game);
	}
	for (y = 0; y < MINIMAP_SIZE; y++)
	{
		put_pixel(left, top + y, 0x000000, game);
		put_pixel(left + MINIMAP_SIZE, top + y, 0x000000, game);
	}
}

void	draw_player_minimap(t_cub3d *game)
{
	int	cx;
	int	cy;

	cx = WIDTH - MINIMAP_SIZE / 2 - MINIMAP_MARGIN;
	cy = HEIGHT - MINIMAP_SIZE / 2 - MINIMAP_MARGIN;
	draw_square(cx - 3, cy - 3, 6, 0x00FF00, game);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	draw_minimap(t_cub3d *game)
{
	int		map_x;
	int		map_y;
	int		screen_x;
	int		screen_y;
	int		block;
	int		color;
	float	world_x;
	float	world_y;

	block = BLOCK * MINIMAP_SCALE;
	color = 0x888888;
	for (map_y = 0; game->map[map_y]; map_y++)
	{
		for (map_x = 0; game->map[map_y][map_x]; map_x++)
		{
			if (game->map[map_y][map_x] != '1')
				continue ;
			/* posição do bloco no mundo */
			world_x = map_x * BLOCK;
			world_y = map_y * BLOCK;
			/* converte mundo → minimapa (player centralizado) */
			screen_x = WIDTH - MINIMAP_SIZE - MINIMAP_MARGIN + (world_x
					- game->player.x) * MINIMAP_SCALE + MINIMAP_SIZE / 2;
			screen_y = HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + (world_y
					- game->player.y) * MINIMAP_SCALE + MINIMAP_SIZE / 2;
			/* recorte da janela do minimapa */
			if (screen_x < WIDTH - MINIMAP_SIZE - MINIMAP_MARGIN
				|| screen_x > WIDTH - MINIMAP_MARGIN || screen_y < HEIGHT
				- MINIMAP_SIZE - MINIMAP_MARGIN || screen_y > HEIGHT
				- MINIMAP_MARGIN)
				continue ;
			draw_square(screen_x, screen_y, block, color, game);
		}
	}
}
