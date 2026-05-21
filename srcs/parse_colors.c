/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:52:14 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/17 19:42:54 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_isdigit2(char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
	{
		if (c[i] >= 48 && c[i] <= 57)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*process_rgb_line(char *line, t_cub3d *game)
{
	game->tab = ft_split(line, ' ');
	if (!game->tab || !game->tab[1])
		return (NULL);
	game->rgb = ft_split(game->tab[1], ',');
	ft_free_split(game->tab);
	if (!game->rgb || !game->rgb[0] || !game->rgb[1] || !game->rgb[2])
	{
		ft_free_split(game->rgb);
		return (NULL);
	}
	if (ft_isdigit2(game->rgb[0]))
		game->r_hex = ft_int_to_hex(ft_atoi(game->rgb[0]));
	else
		exit(1);
	game->g_hex = ft_int_to_hex(ft_atoi(game->rgb[1]));
	game->b_hex = ft_int_to_hex(ft_atoi(game->rgb[2]));
	ft_free_split(game->rgb);
	game->tmp = ft_strjoin(game->r_hex, game->g_hex);
	game->final_hex = ft_strjoin(game->tmp, game->b_hex);
	free(game->r_hex);
	free(game->g_hex);
	free(game->b_hex);
	free(game->tmp);
	return (game->final_hex);
}

static void	process_line(t_cub3d *game, char *line)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		if (game->floor)
			free(game->floor);
		game->floor = process_rgb_line(line, game);
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		if (game->ceiling)
			free(game->ceiling);
		game->ceiling = process_rgb_line(line, game);
	}
}

void	parse_colors(t_cub3d *game, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		process_line(game, line);
		free(line);
		if (game->floor && game->ceiling)
			break ;
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
