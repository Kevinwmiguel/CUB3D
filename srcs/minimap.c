/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:28:52 by kwillian          #+#    #+#             */
/*   Updated: 2026/02/01 18:42:03 by kwillian         ###   ########.fr       */
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
	x = 0;
	y = 0;
	while (x < MINIMAP_SIZE)
	{
		put_pixel(left + x, top, 0x000000, game);
		put_pixel(left + x, top + MINIMAP_SIZE, 0x000000, game);
		x++;
	}
	while (y < MINIMAP_SIZE)
	{
		put_pixel(left, top + y, 0x000000, game);
		put_pixel(left + MINIMAP_SIZE, top + y, 0x000000, game);
		y++;
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

void	draw_minimap_block(t_cub3d *game, int map_x, int map_y)
{
	int		screen_x;
	int		screen_y;
	int		block;
	float	world_x;

	block = BLOCK * MINIMAP_SCALE;
	world_x = map_x * BLOCK;
	screen_x = WIDTH - MINIMAP_SIZE - MINIMAP_MARGIN + (world_x
			- game->player.x) * MINIMAP_SCALE + MINIMAP_SIZE / 2;
	world_x = map_y * BLOCK;
	screen_y = HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + (world_x
			- game->player.y) * MINIMAP_SCALE + MINIMAP_SIZE / 2;
	if (screen_x < WIDTH - MINIMAP_SIZE - MINIMAP_MARGIN)
		return ;
	if (screen_x > WIDTH - MINIMAP_MARGIN)
		return ;
	if (screen_y < HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN)
		return ;
	if (screen_y > HEIGHT - MINIMAP_MARGIN)
		return ;
	draw_square(screen_x, screen_y, block, 0x888888, game);
}

void	draw_minimap(t_cub3d *game)
{
	int	map_x;
	int	map_y;

	map_y = 0;
	while (game->map[map_y])
	{
		map_x = 0;
		while (game->map[map_y][map_x])
		{
			if (game->map[map_y][map_x] == '1')
				draw_minimap_block(game, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
}