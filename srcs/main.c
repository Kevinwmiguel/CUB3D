/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:15:43 by kwillian          #+#    #+#             */
/*   Updated: 2026/04/27 22:53:58 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	main(int argc, char **argv)
{
	t_cub3d	game;

	if (argc == 2)
	{
		init_cub3d(&game, argv[1]);
		mlx_hook(game.win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game);
		mlx_hook(game.win, 17, 0, destroy_game, &game);
		mlx_loop_hook(game.mlx, draw_loop, &game);
		mlx_loop(game.mlx);
		return (0);
	}
	ft_putstr_fd("Wrong number of arguments\n", 2);
	return (1);
}
