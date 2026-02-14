/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:28:30 by kwillian          #+#    #+#             */
/*   Updated: 2026/02/14 14:36:17 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ready_go(t_cub3d *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Imersive");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

static void	init_values(t_cub3d *game)
{
	init_player(&game->player);
	game->tab = NULL;
	game->fov = (PI / 3);
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
}

static void	load_resources(t_cub3d *game, char *path)
{
	get_textures(game, path);
	game->floor = get_floor(path);
	game->ceiling = get_ceiling(path);
	parse_colors(game, path);
	if (!game->floor || !game->ceiling)
		printf("Erro: Cores não encontradas ou mal formatadas!\n");
	game->map = get_map(path);
}

static void	validate_and_start(t_cub3d *game)
{
	if (!validate_map(game, game->map))
	{
		printf("Invalid map\n");
		destroy_game(game);
	}
	set_player_from_map(game);
	ready_go(game);
}

void	init_cub3d(t_cub3d *game, char *path)
{
	init_values(game);
	load_resources(game, path);
	validate_and_start(game);
}
