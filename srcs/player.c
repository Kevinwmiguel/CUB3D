/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:36:45 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/08 01:36:05 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2 - 15;
	player->y = HEIGHT / 2 - 15;
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;

	player->left_rotate = false;
	player->right_rotate = false;
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == ESC)
	{
		exit(0);
	}
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

bool	touch_wall(float px, float py, t_cub3d *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(px / BLOCK);
	map_y = (int)(py / BLOCK);

	if (map_x < 0 || map_y < 0
		|| map_y >= HEIGHT
		|| map_x >= WIDTH)
		return (true);

	if (game->map[map_y][map_x] == '1')
		return (true);
	return (false);
}

void	move_player(t_player *player, t_cub3d *game)
{
	float	speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;
	float	next_x;
	float	next_y;

	speed = 3.0;
	angle_speed = 0.03;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);

	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;

	next_x = player->x;
	next_y = player->y;

	if (player->key_up)
	{
		next_x += cos_angle * speed;
		next_y += sin_angle * speed;
	}
	if (player->key_down)
	{
		next_x -= cos_angle * speed;
		next_y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		next_x += sin_angle * speed;
		next_y -= cos_angle * speed;
	}
	if (player->key_right)
	{
		next_x -= sin_angle * speed;
		next_y += cos_angle * speed;
	}
	if (!touch_wall(next_x + PLAYER_RADIUS, player->y, game)
		&& !touch_wall(next_x - PLAYER_RADIUS, player->y, game))
		player->x = next_x;
	if (!touch_wall(player->x, next_y + PLAYER_RADIUS, game)
		&& !touch_wall(player->x, next_y - PLAYER_RADIUS, game))
		player->y = next_y;
}
