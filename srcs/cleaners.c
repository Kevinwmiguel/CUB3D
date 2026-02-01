/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:12:38 by kwillian          #+#    #+#             */
/*   Updated: 2026/02/01 18:22:26 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	free_textures_ceiling(t_cub3d *game)
{
	int	i;

	i = 0;
	if (game->floor)
		free(game->floor);
	if (game->ceiling)
		free(game->ceiling);
	while (i < 4)
	{
		if (game->tex[i].img_path)
			free(game->tex[i].img_path);
		i++;
	}
}

void	exit_clean(t_cub3d *game)
{
	fcleaner(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

void	fcleaner(t_cub3d *game)
{
	int	i;

	i = 0;
	if (!game)
		return ;
	if (game->map)
	{
		while (game->map[i])
			free(game->map[i++]);
		free(game->map);
		game->map = NULL;
	}
	free_textures_ceiling(game);
}

int	destroy_game(t_cub3d *game)
{
	int	i;

	if (!game)
		exit(1);
	if (game->map)
	{
		i = 0;
		while (game->map[i])
			free(game->map[i++]);
		free(game->map);
	}
	i = 0;
	free_textures_ceiling(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}
