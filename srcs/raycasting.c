/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:28:14 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/08 17:18:10 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	cast_rays_3d(t_cub3d *game)
{
	float	ray_angle;
	float	step;
	int		i;

	step = game->fov / WIDTH;
	ray_angle = game->player.angle - (game->fov / 2);
	i = 0;
	while (i < WIDTH)
	{
		draw_line(game, ray_angle, i);
		ray_angle += step;
		i++;
	}
}

void	cast_rays_2d(t_cub3d *game)
{
	float	ray_angle;
	float	step;
	float	ray_x;
	float	ray_y;
	int		i;

	step = game->fov / 120;
	ray_angle = game->player.angle - (game->fov / 2);
	i = 0;
	while (i < 120)
	{
		ray_x = game->player.x;
		ray_y = game->player.y;
		while (!touch_wall(ray_x, ray_y, game))
		{
			put_pixel(ray_x - game->player.x + WIDTH / 2, ray_y - game->player.y
				+ HEIGHT / 2, 0xFF0000, game);
			ray_x += cos(ray_angle);
			ray_y += sin(ray_angle);
		}
		ray_angle += step;
		i++;
	}
}

void	render_rays(t_cub3d *game)
{
	int		i;
	float	ray_angle;
	float	fov;
	float	step;

	fov = PI / 3;
	step = fov / WIDTH;
	ray_angle = game->player.angle - (fov / 2);
	i = 0;
	while (i < WIDTH)
	{
		draw_line(game, ray_angle, i);
		ray_angle += step;
		i++;
	}
}
