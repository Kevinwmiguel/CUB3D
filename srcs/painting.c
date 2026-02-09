/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 23:56:10 by kwillian          #+#    #+#             */
/*   Updated: 2026/02/01 23:59:37 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	paint_floor_and_ceiling(t_cub3d *game)
{
	int	color_floor;
	int	color_ceiling;
	int	*pixels;
	int	x;
	int	y;

	color_floor = hex_to_int(game->floor);
	color_ceiling = hex_to_int(game->ceiling);
	pixels = (int *)game->data;
	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				pixels[y * (game->size_line / 4) + x] = color_ceiling;
			else
				pixels[y * (game->size_line / 4) + x] = color_floor;
			x++;
		}
		y++;
	}
}

void	put_pixel(int x, int y, int color, t_cub3d *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}
