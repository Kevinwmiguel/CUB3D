/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:36:45 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/09 18:21:00 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	set_player_from_map(t_cub3d *game)
{
	int x;
	int y;
	char c;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			c = game->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.x = (x + 0.5) * BLOCK;
				game->player.y = (y + 0.5) * BLOCK;

				if (c == 'N') game->player.angle = 3 * PI / 2;
				if (c == 'S') game->player.angle = PI / 2;
				if (c == 'E') game->player.angle = 0;
				if (c == 'W') game->player.angle = PI;

				game->map[y][x] = '0';
				return;
			}
			x++;
		}
		y++;
	}
}


void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->angle = 0;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}



// void	init_player(t_player *player)
// {
// 	player->x = 2.5 * BLOCK;
// 	player->y = 2.5 * BLOCK;
// 	player->angle = PI / 2;
//
// 	player->key_up = false;
// 	player->key_down = false;
// 	player->key_left = false;
// 	player->key_right = false;
// 	player->left_rotate = false;
// 	player->right_rotate = false;
// }

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

// bool	touch_wall(float px, float py, t_cub3d *game)
// {
// 	int	map_x;
// 	int	map_y;
//
// 	map_x = (int)(px / BLOCK);
// 	map_y = (int)(py / BLOCK);
//
// 	if (map_x < 0 || map_y < 0
// 		|| map_y >= HEIGHT
// 		|| map_x >= WIDTH)
// 		return (true);
//
// 	if (game->map[map_y][map_x] == '1')
// 		return (true);
// 	return (false);
// }

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

void	move_player(t_player *player, t_cub3d *game)
{
	float	speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;
	float	next_x;
	float	next_y;

	speed = 3.0;
	angle_speed = 0.08;

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
