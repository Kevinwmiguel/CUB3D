/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:48:59 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/13 22:49:06 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

bool	touch_wall(float px, float py, t_cub3d *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(px / BLOCK);
	map_y = (int)(py / BLOCK);
	if (map_x < 0 || map_y < 0)
		return (true);
	if (!game->map[map_y])
		return (true);
	if (!game->map[map_y][map_x])
		return (true);
	if (game->map[map_y][map_x] == '1')
		return (true);
	return (false);
}

void	player_moving(t_player *player)
{
	if (player->key_up)
	{
		player->next_x += player->cos_angle * player->speed;
		player->next_y += player->sin_angle * player->speed;
	}
	if (player->key_down)
	{
		player->next_x -= player->cos_angle * player->speed;
		player->next_y -= player->sin_angle * player->speed;
	}
	if (player->key_left)
	{
		player->next_x += player->sin_angle * player->speed;
		player->next_y -= player->cos_angle * player->speed;
	}
	if (player->key_right)
	{
		player->next_x -= player->sin_angle * player->speed;
		player->next_y += player->cos_angle * player->speed;
	}
}

void	move_player(t_player *player, t_cub3d *game)
{
	player->speed = 3.0;
	player->angle_speed = 0.08;
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= player->angle_speed;
	if (player->right_rotate)
		player->angle += player->angle_speed;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
	player->next_x = player->x;
	player->next_y = player->y;
	player_moving(player);
	if (!touch_wall(player->next_x + PLAYER_RADIUS, player->y, game)
		&& !touch_wall(player->next_x - PLAYER_RADIUS, player->y, game))
		player->x = player->next_x;
	if (!touch_wall(player->x, player->next_y + PLAYER_RADIUS, game)
		&& !touch_wall(player->x, player->next_y - PLAYER_RADIUS, game))
		player->y = player->next_y;
}
