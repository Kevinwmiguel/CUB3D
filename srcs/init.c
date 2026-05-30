/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:28:30 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/30 15:43:34 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	load_resources(t_cub3d *game, char *path)
{
	get_textures(game, path);
	game->floor = get_floor(game, path);
	game->ceiling = get_ceiling(game, path);
	parse_colors(game, path);
	if (!game->floor || !game->ceiling)
		return (printf("Error\nColor not found or in the wrong format\n"), -1);
	game->map = get_map(path);
	return (0);
}

static int	validate_and_start(t_cub3d *game)
{
	if (!validate_map(game, game->map))
	{
		printf("Error\nInvalid map or more than one player found\n");
		destroy_game(game, 1);
		return (-1);
	}
	set_player_from_map(game);
	calculate_map_dimensions(game);
	return (0);
}

int	init_cub3d(t_cub3d *game, char *path)
{
	game->fov = (PI / 3);
	if (load_resources(game, path) == -1)
		return (-1);
	if (validate_and_start(game) == -1)
		return (-1);
	ready_go(game);
	return (0);
}
