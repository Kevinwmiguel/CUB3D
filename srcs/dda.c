/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:26:33 by made-jes          #+#    #+#             */
/*   Updated: 2026/05/24 13:24:28 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	calculate_wall_dist(t_dda *dda, t_player *player, float ray_angle)
{
	float	ray_dir_x;
	float	ray_dir_y;

	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	if (dda->side == 0)
		dda->perp_wall_dist = (dda->map_x - player->x / BLOCK
				+ (1 - dda->step_x) / 2) / ray_dir_x;
	else
		dda->perp_wall_dist = (dda->map_y - player->y / BLOCK
				+ (1 - dda->step_y) / 2) / ray_dir_y;
}

void	get_tex_in(t_dda *dda, t_player *player, t_cub3d *game, float ray_angle)
{
	float	wall_x;
	float	ray_dir_x;
	float	ray_dir_y;

	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	if (dda->side == 0)
	{
		if (dda->step_x > 0)
			game->hit.tex_id = 3;
		else
			game->hit.tex_id = 2;
		wall_x = player->y / BLOCK + dda->perp_wall_dist * ray_dir_y;
	}
	else
	{
		if (dda->step_y > 0)
			game->hit.tex_id = 1;
		else
			game->hit.tex_id = 0;
		wall_x = player->x / BLOCK + dda->perp_wall_dist * ray_dir_x;
	}
	wall_x -= floor(wall_x);
	game->hit.wall_x = wall_x;
	game->hit.side = dda->side;
}

float	trace_ray_dda(t_cub3d *game, float angle)
{
	t_dda	dda;
	int		hit;
	float	diff_angle;
	float	corrected_dist;

	init_dda(&dda, &game->player, angle);
	hit = perform_dda(&dda, game);
	if (!hit)
		return (-1.0);
	calculate_wall_dist(&dda, &game->player, angle);
	get_tex_in(&dda, &game->player, game, angle);
	diff_angle = angle - game->player.angle;
	if (diff_angle < -M_PI)
		diff_angle += 2 * M_PI;
	if (diff_angle > M_PI)
		diff_angle -= 2 * M_PI;
	corrected_dist = dda.perp_wall_dist * cos(diff_angle);
	return (corrected_dist * BLOCK);
}
