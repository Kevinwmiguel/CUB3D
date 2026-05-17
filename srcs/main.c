/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:15:43 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/17 20:02:15 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	clean_newline(char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			return ;
		}
		i++;
	}
}

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	in_range_0_255(char *str)
{
	int	n;

	n = ft_atoi(str);
	if (n < 0 || n > 255)
		return (0);
	return (1);
}

static int	check_rgb_format(char *line)
{
	char	**tmp;
	char	**rgb;
	int		i;

	if (!line || (line[0] != 'F' && line[0] != 'C') || line[1] != ' ')
		return (0);

	tmp = ft_split(line, ' ');
	if (!tmp || !tmp[1])
		return (ft_free_split(tmp), 0);

	clean_newline(tmp[1]); // <- mantém isto que já te dei

	rgb = ft_split(tmp[1], ',');
	ft_free_split(tmp);

	if (!rgb)
		return (0);

	i = 0;
	while (rgb[i])
		i++;

	if (i != 3)
		return (ft_free_split(rgb), 0);

	if (!is_number(rgb[0]) || !is_number(rgb[1]) || !is_number(rgb[2]))
		return (ft_free_split(rgb), 0);

	if (!in_range_0_255(rgb[0]) || !in_range_0_255(rgb[1]) || !in_range_0_255(rgb[2]))
		return (ft_free_split(rgb), 0);

	ft_free_split(rgb);
	return (1);
}

static int	precheck_colors(char *path)
{
	int		fd;
	char	*line;
	int		f;
	int		c;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);

	f = 0;
	c = 0;
	line = get_next_line(fd);

	while (line)
	{
		if (line[0] == 'F' && line[1] == ' ')
		{
			if (!check_rgb_format(line))
				return (free(line), close(fd), 0);
			f = 1;
		}
		else if (line[0] == 'C' && line[1] == ' ')
		{
			if (!check_rgb_format(line))
				return (free(line), close(fd), 0);
			c = 1;
		}

		free(line);
		line = get_next_line(fd);
	}

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
