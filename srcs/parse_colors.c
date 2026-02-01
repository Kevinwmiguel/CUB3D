/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:52:14 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/31 18:44:01 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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
	game->r_hex = ft_int_to_hex(ft_atoi(game->rgb[0]));
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
		if (line[0] == 'F' && line[1] == ' ')
			game->floor = process_rgb_line(line, game);
		else if (line[0] == 'C' && line[1] == ' ')
			game->ceiling = process_rgb_line(line, game);
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
