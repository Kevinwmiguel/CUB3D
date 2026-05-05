/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:28:30 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/05 20:52:29 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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

static int	load_resources(t_cub3d *game, char *path)
{
	get_textures(game, path);
	game->floor = get_floor(path);
	game->ceiling = get_ceiling(path);
	parse_colors(game, path);
	if (!game->floor || !game->ceiling)
		return (printf("Erro: Cores não encontradas ou mal formatadas!\n"), -1);
	game->map = get_map(path);
	return (0);
}

static int	validate_and_start(t_cub3d *game)
{
	if (!validate_map(game, game->map))
	{
		printf("Invalid map\n");
		destroy_game(game);
		return (-1);
	}
	set_player_from_map(game);
	calculate_map_dimensions(game);
	ready_go(game);
	return (0);
}

int	init_cub3d(t_cub3d *game, char *path)
{
	init_values(game);
	if (load_resources(game, path) == -1)
		return (-1);
	if (validate_and_start(game) == -1)
		return (-1);
	return (0);
}
