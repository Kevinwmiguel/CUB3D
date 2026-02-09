/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:15:43 by kwillian          #+#    #+#             */
/*   Updated: 2026/02/09 00:59:08 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_cub3d(t_cub3d *game, char *path)
{
	init_player(&game->player);
	game->tab = NULL;
	game->colorhelp = 0;
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

float	fixed_dist(t_cub3d *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = game->x2 - game->x1;
	delta_y = game->y2 - game->y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
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
