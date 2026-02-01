/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:15:43 by kwillian          #+#    #+#             */
/*   Updated: 2026/02/01 18:15:34 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	paint_floor_and_ceiling(t_cub3d *game)
{
	int	color_floor;
	int	color_ceiling;
	int	*pixels;
	int	x;
	int	y;

	color_floor = hex_to_int(game->floor);
	color_ceiling = hex_to_int(game->ceiling);
	pixels = (int *)game->data;
	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				pixels[y * (game->size_line / 4) + x] = color_ceiling;
			else
				pixels[y * (game->size_line / 4) + x] = color_floor;
			x++;
		}
		y++;
	}
}

void	put_pixel(int x, int y, int color, t_cub3d *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_cub3d *game)
{
	while (game->draw_count < size)
	{
		put_pixel(x + game->draw_count, y, color, game);
		game->draw_count++;
	}
	game->draw_count = 0;
	while (game->draw_count < size)
	{
		put_pixel(x, y + game->draw_count, color, game);
		game->draw_count++;
	}
	game->draw_count = 0;
	while (game->draw_count < size)
	{
		put_pixel(x + size, y + game->draw_count, color, game);
		game->draw_count++;
	}
	game->draw_count = 0;
	while (game->draw_count < size)
	{
		put_pixel(x + game->draw_count, y + size, color, game);
		game->draw_count++;
	}
}

void	clear_image(t_cub3d *game)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

void	init_cub3d(t_cub3d *game, char *path)
{
	init_player(&game->player);
	game->tab = NULL;
	game->rgb = NULL;
	game->r_hex = NULL;
	game->g_hex = NULL;
	game->b_hex = NULL;
	game->tmp = NULL;
	game->draw_count = 0;
	game->final_hex = NULL;
	game->tex[0].img_path = NULL;
	game->tex[1].img_path = NULL;
	game->tex[2].img_path = NULL;
	game->tex[3].img_path = NULL;
	get_textures(game, path);
	game->floor = get_floor(path);
	game->ceiling = get_ceiling(path);
	parse_colors(game, path);
	if (!game->floor || !game->ceiling)
		printf("Erro: Cores não encontradas ou mal formatadas!\n");
	game->map = get_map(path);
	if (!validate_map(game, game->map))
	{
		printf("Mapa inválido\n");
		destroy_game(game);
		exit(1);
	}
	set_player_from_map(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Imersive");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

bool	touch(float px, float py, t_cub3d *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_cub3d *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_player(t_cub3d *game)
{
	int	cx;
	int	cy;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	draw_square(cx - 15, cy - 15, 10, 0x00FF00, game);
}

int	draw_loop(t_cub3d *game)
{
	move_player(&game->player, game);
	clear_image(game);
	paint_floor_and_ceiling(game);
	if (DEBUG)
	{
		draw_map(game);
		draw_player(game);
		cast_rays_2d(game);
	}
	else
	{
		cast_rays_3d(game);
		draw_minimap(game);
		draw_player_minimap(game);
		draw_minimap_border(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	game;

	if (argc == 2)
	{
		init_cub3d(&game, argv[1]);
		mlx_hook(game.win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game);
		mlx_hook(game.win, 17, 0, destroy_game, &game);
		mlx_loop_hook(game.mlx, draw_loop, &game);
		mlx_loop(game.mlx);
	}
	return (0);
}
