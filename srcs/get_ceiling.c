/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ceiling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:04:50 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/17 13:39:43 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char	*build_color(char **temp2)
{
	char	*r;
	char	*g;
	char	*b;
	char	*color;
	char	*tmp;

	color = NULL;
	if (temp2 && temp2[0] && temp2[1] && temp2[2])
	{
		r = ft_int_to_hex(ft_atoi(temp2[0]));
		g = ft_int_to_hex(ft_atoi(temp2[1]));
		b = ft_int_to_hex(ft_atoi(temp2[2]));
		tmp = ft_strjoin(r, g);
		color = ft_strjoin(tmp, b);
		return (free(tmp), free(r), free(g), free(b), color);
	}
	return (color);
}

char	*fc_help(t_cub3d *game, char **temp, char *color, int fd)
{
	char	**rgb_split;

	while (game->line)
	{
		if (game->line[0] == game->color_letter && game->line[1] == ' ')
		{
			temp = ft_split(game->line, ' ');
			rgb_split = ft_split(temp[1], ',');
			color = build_color(rgb_split);
			ft_free_split(rgb_split);
			ft_free_split(temp);
			free(game->line);
			break ;
		}
		free(game->line);
		game->line = get_next_line(fd);
	}
	game->line = get_next_line(fd);
	while (game->line)
	{
		free(game->line);
		game->line = get_next_line(fd);
	}
	return (close(fd), color);
}

char	*get_ceiling(t_cub3d *game, char *path)
{
	int		fd;
	char	*color;
	char	**temp;

	color = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	game->line = get_next_line(fd);
	temp = NULL;
	game->color_letter = 'C';
	color = fc_help(game, temp, color, fd);
	return (color);
}
