/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 23:55:24 by kwillian          #+#    #+#             */
/*   Updated: 2026/02/09 00:49:41 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	draw_player(t_cub3d *game)
{
	int	cx;
	int	cy;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	game->colorhelp = 0x00FF00;
	draw_square(cx - 15, cy - 15, 10, game);
}

int	draw_loop(t_cub3d *game)
{
	move_player(&game->player, game);
	clear_image(game);
	paint_floor_and_ceiling(game);
	if (DEBUG)
	{
		draw_map(game);
		draw_player(game);
		cast_rays_2d(game);
	}
	else
	{
		cast_rays_3d(game);
		draw_minimap(game);
		draw_player_minimap(game);
		draw_minimap_border(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

void	draw_square(int x, int y, int size, t_cub3d *game)
{
	while (game->draw_count < size)
	{
		put_pixel(x + game->draw_count, y, game->colorhelp, game);
		game->draw_count++;
	}
	game->draw_count = 0;
	while (game->draw_count < size)
	{
		put_pixel(x, y + game->draw_count, game->colorhelp, game);
		game->draw_count++;
	}
	game->draw_count = 0;
	while (game->draw_count < size)
	{
		put_pixel(x + size, y + game->draw_count, game->colorhelp, game);
		game->draw_count++;
	}
	game->draw_count = 0;
	while (game->draw_count < size)
	{
		put_pixel(x + game->draw_count, y + size, game->colorhelp, game);
		game->draw_count++;
	}
}
