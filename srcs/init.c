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

static void	load_textures(t_cub3d *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!game->tex[i].img_path)
		{
			printf("Error\nMissing texture path\n");
			destroy_game(game, 1);
		}
		game->tex[i].img = mlx_xpm_file_to_image(game->mlx,
				game->tex[i].img_path, &game->tex[i].width,
				&game->tex[i].height);
		if (!game->tex[i].img)
		{
			printf("Error\nCould not load texture: %s\n",
				game->tex[i].img_path);
			destroy_game(game, 1);
		}
		game->tex[i].data = mlx_get_data_addr(game->tex[i].img,
				&game->tex[i].bpp, &game->tex[i].size_line,
				&game->tex[i].endian);
		i++;
	}
}

void	ready_go(t_cub3d *game)
{
	game->mlx = mlx_init();
	load_textures(game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
