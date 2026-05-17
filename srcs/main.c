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

static int	handle_color_line(char *line, int *f, int *c)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		if (!check_rgb_format(line))
			return (0);
		*f = 1;
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		if (!check_rgb_format(line))
			return (0);
		*c = 1;
	}
	return (1);
}

static int	process_colors_loop(int fd, int *f, int *c)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!handle_color_line(line, f, c))
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

static int	precheck_colors(char *path)
{
	int	fd;
	int	f;
	int	c;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	f = 0;
	c = 0;
	if (!process_colors_loop(fd, &f, &c))
		return (close(fd), 0);
	close(fd);
	return (f && c);
}

int	main(int argc, char **argv)
{
	t_cub3d	game;

	if (argc == 2)
	{
		if (check_map_name(argv[1]))
			return (ft_putstr_fd("Invalid map name\n", 2), 1);
		if (!precheck_colors(argv[1]))
			return (ft_putstr_fd("Error: invalid RGB format\n", 2), 1);
		if (init_cub3d(&game, argv[1]) == -1)
			return (destroy_game(&game, 1), 1);
		mlx_hook(game.win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game);
		mlx_hook(game.win, 17, 0, destroy_game, &game);
		mlx_loop_hook(game.mlx, draw_loop, &game);
		mlx_loop(game.mlx);
	}
	ft_putstr_fd("Wrong number of arguments\n", 2);
	return (1);
}
