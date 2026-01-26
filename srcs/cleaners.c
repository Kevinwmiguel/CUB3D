/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:12:38 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/26 13:23:28 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void free_textures(t_cub3d *game)
{
    int i = 0;
    while (i < 4)
    {
        if (game->tex[i].img_path)
            free(game->tex[i].img_path);
        i++;
    }
}

void exit_clean(t_cub3d *game)
{
    fcleaner(game);
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    exit(0);
}

void fcleaner(t_cub3d *game)
{
    int i = 0;

    if (!game)
        return;

    if (game->map)
    {
        while (game->map[i])
            free(game->map[i++]);
        free(game->map);
        game->map = NULL;
    }
	free(game->floor);
	free(game->ceiling);
	free_textures(game);
}
