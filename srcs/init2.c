/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:08:01 by made-jes          #+#    #+#             */
/*   Updated: 2026/02/24 21:42:41 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	load_textures(t_cub3d *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->tex[i].img = mlx_xpm_file_to_image(game->mlx,
				game->tex[i].img_path, &game->tex[i].width,
				&game->tex[i].height);
		if (!game->tex[i].img)
		{
			printf("Error: could not load texture: %s\n",
				game->tex[i].img_path);
			destroy_game(game);
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
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Imersive");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	load_textures(game);
}
