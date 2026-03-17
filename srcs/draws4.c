/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:26:33 by made-jes          #+#    #+#             */
/*   Updated: 2026/03/13 23:29:28 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	hit_image(t_cub3d *g, float *pos, float step_x, float step_y)
{
	if (g->hit.side == 0)
	{
		if (step_x > 0)
			g->hit.tex_id = 3;
		else
			g->hit.tex_id = 2;
		g->hit.wall_x = fmod(pos[1], BLOCK) / BLOCK;
	}
	else
	{
		if (step_y > 0)
			g->hit.tex_id = 1;
		else
			g->hit.tex_id = 0;
		g->hit.wall_x = fmod(pos[0], BLOCK) / BLOCK;
	}
}

static int	get_side(t_cub3d *g, float angle, float px, float py)
{
	float	rx;
	float	ry;
	int		sx;
	int		sy;

	rx = px;
	ry = py;
	sx = 0;
	sy = 0;
	while (!touch_wall(rx, py, g))
	{
		rx += cos(angle);
		sx++;
	}
	while (!touch_wall(px, ry, g))
	{
		ry += sin(angle);
		sy++;
	}
	if (sx <= sy)
		return (0);
	return (1);
}

void	trace_ray(t_cub3d *g, float angle, float *pos)
{
	float	step_x;
	float	step_y;
	int		safety;

	step_x = cos(angle);
	step_y = sin(angle);
	g->hit.side = get_side(g, angle, pos[0], pos[1]);
	safety = 0;
	while (!touch_wall(pos[0], pos[1], g))
	{
		pos[0] += step_x;
		pos[1] += step_y;
		if (++safety > 10000)
			break ;
	}
	hit_image(g, pos, step_x, step_y);
}
	