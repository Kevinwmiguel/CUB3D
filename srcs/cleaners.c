/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:12:38 by kwillian          #+#    #+#             */
/*   Updated: 2026/04/29 21:06:56 by made-jes         ###   ########.fr       */
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
