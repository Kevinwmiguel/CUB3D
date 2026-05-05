/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 21:04:55 by made-jes          #+#    #+#             */
/*   Updated: 2026/05/05 21:07:40 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_dda_x(t_dda *dda, t_player *player, float ray_dir_x)
{
	if (ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = ((player->x / BLOCK) - dda->map_x)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - (player->x / BLOCK))
			* dda->delta_dist_x;
	}
}

void	init_dda(t_dda *dda, t_player *player, float ray_angle)
{
	float	ray_dir_x;
	float	ray_dir_y;

	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	dda->map_x = (int)(player->x / BLOCK);
	dda->map_y = (int)(player->y / BLOCK);
	dda->delta_dist_x = fabs(1 / ray_dir_x);
	dda->delta_dist_y = fabs(1 / ray_dir_y);
	init_dda_x(dda, player, ray_dir_x);
	if (ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = ((player->y / BLOCK) - dda->map_y)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - (player->y / BLOCK))
			* dda->delta_dist_y;
	}
}

void	dda_step(t_dda *dda)
{
	if (dda->side_dist_x < dda->side_dist_y)
	{
		dda->side_dist_x += dda->delta_dist_x;
		dda->map_x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_dist_y += dda->delta_dist_y;
		dda->map_y += dda->step_y;
		dda->side = 1;
	}
}

int	perform_dda(t_dda *dda, t_cub3d *game)
{
	int	hit;
	int	safety;

	hit = 0;
	safety = 0;
	while (hit == 0 && safety < 1000)
	{
		dda_step(dda);
		if (dda->map_y < 0 || dda->map_y >= game->y_map
			|| dda->map_x < 0 || dda->map_x >= game->x_map)
			return (0);
		if (game->map[dda->map_y][dda->map_x] == '1')
			hit = 1;
		safety++;
	}
	return (hit);
}
