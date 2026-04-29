/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:26:33 by made-jes          #+#    #+#             */
/*   Updated: 2026/04/29 23:17:55 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	hit_image(t_cub3d *g, float *pos, t_rayhit *r)
{
	int		map_x;
	int		map_y;
	int		prev_map_x;
	int		prev_map_y;
	float	hit_x;
	float	hit_y;

	map_x = (int)(pos[0] / BLOCK);
	map_y = (int)(pos[1] / BLOCK);
	prev_map_x = (int)(r->prev_x / BLOCK);
	prev_map_y = (int)(r->prev_y / BLOCK);
	hit_x = pos[0] - r->step_x;
	hit_y = pos[1] - r->step_y;
	if (map_x != prev_map_x)
	{
		if (r->step_x > 0)
			g->hit.tex_id = 3;
		else
			g->hit.tex_id = 2;
		g->hit.wall_x = fmod(hit_y, BLOCK) / BLOCK;
	}
	else if (map_y != prev_map_y)
	{
		if (r->step_y > 0)
			g->hit.tex_id = 1;
		else
			g->hit.tex_id = 0;
		g->hit.wall_x = fmod(hit_x, BLOCK) / BLOCK;
	}
	if (g->hit.wall_x < 0)
		g->hit.wall_x += 1.0;
}

void	trace_ray(t_cub3d *g, float angle, float *pos)
{
	float		step_x;
	float		step_y;
	t_rayhit	r;
	int			safety;

	step_x = cos(angle);
	step_y = sin(angle);
	r.step_x = step_x;
	r.step_y = step_y;
	safety = 0;
	while (!touch_wall(pos[0], pos[1], g))
	{
		r.prev_x = pos[0];
		r.prev_y = pos[1];
		pos[0] += step_x;
		pos[1] += step_y;
		if (++safety > 10000)
			break ;
	}
	hit_image(g, pos, &r);
}
