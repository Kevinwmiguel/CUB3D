/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:15:43 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/06 18:08:52 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	put_pixel(int x, int y, int color, t_cub3d *game)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;

	int index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_cub3d *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + size, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y + size, color, game);
		i++;
	}
}

void	clear_image(t_cub3d *game)
{
	for(int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			put_pixel(x,y, 0, game);
}

void	init_cub3d(t_cub3d *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "FLYING WATERS");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0,0);
}

int	draw_loop(t_cub3d *game)
{
	t_player	*player = &game->player;
	move_player(player);
	clear_image(game);
	draw_square(player->x, player->y, 15, 0x00FF00, game);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	main()
{
	t_cub3d	game;

	init_cub3d(&game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	//draw_square(WIDTH / 2, HEIGHT / 2, 10, 0x00FF00, &game);
	mlx_loop(game.mlx);
	return (0);
}
