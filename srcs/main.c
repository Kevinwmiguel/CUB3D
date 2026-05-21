/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:15:43 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/17 23:07:01 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	main(int argc, char **argv)
{
	t_cub3d	game;

	if (argc == 2)
	{
		if (check_map_name(argv[1]))
			return (ft_putstr_fd("Error\nInvalid map name\n", 2), 1);
		if (!precheck_colors(argv[1]))
			return (ft_putstr_fd("Error\nInvalid RGB format\n", 2), 1);
		if (init_cub3d(&game, argv[1]) == -1)
			return (destroy_game(&game, 1), 1);
		mlx_hook(game.win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game);
		mlx_hook(game.win, 17, 0, destroy_game, &game);
		mlx_loop_hook(game.mlx, draw_loop, &game);
		mlx_loop(game.mlx);
	}
	ft_putstr_fd("Error\nWrong number of arguments\n", 2);
	return (1);
}
