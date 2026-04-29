/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:36:45 by kwillian          #+#    #+#             */
/*   Updated: 2026/04/29 21:05:31 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	start_direction(t_cub3d *game, char c)
{
	if (c == 'N')
		game->player.angle = 3 * PI / 2;
	if (c == 'S')
		game->player.angle = PI / 2;
	if (c == 'E')
		game->player.angle = 0;
	if (c == 'W')
		game->player.angle = PI;
}

void	set_player_from_map(t_cub3d *game)
{
	int		x;
	int		y;
	char	c;

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
				start_direction(game, c);
				game->map[y][x] = '0';
				return ;
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
	player->speed = 0;
	player->angle_speed = 0;
	player->cos_angle = 0;
	player->sin_angle = 0;
	player->next_x = 0;
	player->next_y = 0;
}

int	key_press(int keycode, t_cub3d *game)
{
	if (keycode == W)
		game->player.key_up = true;
	if (keycode == S)
		game->player.key_down = true;
	if (keycode == A)
		game->player.key_left = true;
	if (keycode == D)
		game->player.key_right = true;
	if (keycode == D)
		game->player.key_right = true;
	if (keycode == LEFT)
		game->player.left_rotate = true;
	if (keycode == RIGHT)
		game->player.right_rotate = true;
	if (keycode == ESC)
		destroy_game(game);
	return (0);
}

int	key_release(int keycode, t_cub3d *game)
{
	if (keycode == W)
		game->player.key_up = false;
	if (keycode == S)
		game->player.key_down = false;
	if (keycode == A)
		game->player.key_left = false;
	if (keycode == D)
		game->player.key_right = false;
	if (keycode == LEFT)
		game->player.left_rotate = false;
	if (keycode == RIGHT)
		game->player.right_rotate = false;
	return (0);
}
