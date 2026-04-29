/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ceiling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:04:50 by kwillian          #+#    #+#             */
/*   Updated: 2026/04/29 21:43:35 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static char	*build_ceiling_color(char **temp2)
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
		free(tmp);
		free(r);
		free(g);
		free(b);
	}
	return (color);
}

static char	*ceiling_helper(char *line, char **temp, char *color, int fd)
{
	char	**rgb_split;

	while (line)
	{
		if (line[0] == 'C' && line[1] == ' ')
		{
			temp = ft_split(line, ' ');
			rgb_split = ft_split(temp[1], ',');
			color = build_ceiling_color(rgb_split);
			ft_free_split(rgb_split);
			ft_free_split(temp);
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (color);
}

char	*get_ceiling(char *path)
{
	int		fd;
	char	*line;
	char	*color;
	char	**temp;

	color = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	temp = NULL;
	color = ceiling_helper(line, temp, color, fd);
	return (color);
}
