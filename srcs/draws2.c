/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:09:38 by kwillian          #+#    #+#             */
/*   Updated: 2026/02/09 00:58:39 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	trace_ray(t_player *p, t_cub3d *g, float angle, float *pos)
{
	float	step_x;
	float	step_y;

	step_x = cos(angle);
	step_y = sin(angle);
	while (!touch_wall(pos[0], pos[1], g))
	{
		if (DEBUG)
			put_pixel(pos[0] - p->x + WIDTH / 2,
				pos[1] - p->y + HEIGHT / 2, 0xFFFF00, g);
		pos[0] += step_x;
		pos[1] += step_y;
	}
}

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

static void	draw_wall_column(t_cub3d *g, int col, int start, int end)
{
	while (start < end)
	{
		put_pixel(col, start, 0xE10AFF, g);
		start++;
	}
}

void	draw_line(t_player *p, t_cub3d *game, float angle, int col)
{
	float	pos[2];
	float	dist;
	int		start;
	int		end;

	pos[0] = p->x;
	pos[1] = p->y;
	trace_ray(p, game, angle, pos);
	if (!DEBUG)
	{
		game->x1 = p->x;
		game->y1 = p->y;
		game->x2 = pos[0];
		game->y2 = pos[1];
		dist = fixed_dist(game);
		get_wall_limits(dist, &start, &end);
		draw_wall_column(game, col, start, end);
	}
}
