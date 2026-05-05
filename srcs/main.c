/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:15:43 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/05 20:39:04 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	main(int argc, char **argv)
{
	t_cub3d	game;

	if (argc == 2)
	{
		if (check_map_name(argv[1]))
			return (ft_putstr_fd("Invalid map name\n", 2), 1);
		if (init_cub3d(&game, argv[1]) == -1)
			return (destroy_game(&game), 1);
		mlx_hook(game.win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game);
		mlx_hook(game.win, 17, 0, destroy_game, &game);
		mlx_loop_hook(game.mlx, draw_loop, &game);
		mlx_loop(game.mlx);
	}
	ft_putstr_fd("Wrong number of arguments\n", 2);
	return (1);
}
