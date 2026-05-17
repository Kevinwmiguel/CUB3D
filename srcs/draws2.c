/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:09:38 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/05 21:11:31 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	get_wall_limits(float dist, int *start, int *end)
{
	float	height;

	height = (BLOCK / dist) * (WIDTH / 2);
	*start = (HEIGHT / 2) - (height / 2);
	*end = (HEIGHT / 2) + (height / 2);
	if (*start < 0)
		*start = 0;
	if (*end > HEIGHT)
		*end = HEIGHT;
}

static void	init_wall(t_cub3d *g, t_wall *w, int start, float dist)
{
	w->tex = &g->tex[g->hit.tex_id];
	w->tex_x = (int)(g->hit.wall_x * w->tex->width);
	if (w->tex_x >= w->tex->width)
		w->tex_x = w->tex->width - 1;
	w->wall_height = (BLOCK / dist) * (WIDTH / 2);
	w->step = (float)w->tex->height / (w->wall_height * 2);
	w->tex_pos = ((float)start - (HEIGHT / 2) + w->wall_height) * w->step;
}

static void	draw_wall_column(t_cub3d *g, t_wcol *wc)
{
	t_wall	w;
	int		index;
	int		color;
	int		s;

	init_wall(g, &w, wc->start, wc->dist);
	s = wc->start;
	while (s < wc->end)
	{
		w.tex_y = (int)w.tex_pos % w.tex->height;
		if (w.tex_y < 0)
			w.tex_y = 0;
		w.tex_pos += w.step;
		index = w.tex_y * w.tex->size_line + w.tex_x * w.tex->bpp / 8;
		color = *(int *)(w.tex->data + index);
		put_pixel(wc->col, s, color, g);
		s++;
	}
}

void	draw_line(t_cub3d *game, float angle, int col)
{
	float	dist;
	int		start;
	int		end;
	t_wcol	wc;

	dist = trace_ray_dda(game, angle);
	if (dist < 0)
		return ;
	get_wall_limits(dist, &start, &end);
	wc.col = col;
	wc.start = start;
	wc.end = end;
	wc.dist = dist;
	draw_wall_column(game, &wc);
}
