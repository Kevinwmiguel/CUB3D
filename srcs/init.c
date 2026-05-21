/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:28:30 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/18 16:10:11 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	init_values(t_cub3d *game)
{
	game->line = NULL;
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->map = NULL;
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
	game->floor = NULL;
	game->ceiling = NULL;
}

static int	load_resources(t_cub3d *game, char *path)
{
	get_textures(game, path);
	game->floor = get_floor(game, path);
	game->ceiling = get_ceiling(game, path);
	if (!game->floor || !game->ceiling)
		return (printf("Error\nColor not found or in the wrong format\n"), -1);
	game->map = get_map(path);
	return (0);
}

static int	validate_and_start(t_cub3d *game)
{
	if (!validate_map(game, game->map))
	{
		printf("Error\nInvalid map!\n");
		destroy_game(game, 1);
		return (-1);
	}
	set_player_from_map(game);
	calculate_map_dimensions(game);
	return (0);
}

int	init_cub3d(t_cub3d *game, char *path)
{
	init_values(game);
	if (load_resources(game, path) == -1)
		return (-1);
	if (validate_and_start(game) == -1)
		return (-1);
	ready_go(game);
	return (0);
}
