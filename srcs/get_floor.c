/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:56:40 by kwillian          #+#    #+#             */
/*   Updated: 2026/02/24 20:09:06 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

static char	*build_floor_color(char **temp2)
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
		color = ft_strjoin(color, b);
		free(tmp);
		free(r);
		free(g);
		free(b);
	}
	return (color);
}

static char	*floor_helper(char *line, char **temp, char *color, int fd)
{
	while (line)
	{
		if (line[0] == 'F' && line[1] == ' ')
		{
			temp = ft_split(line, ' ');
			color = build_floor_color(ft_split(temp[1], ','));
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

char	*get_floor(char *path)
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
	color = floor_helper(line, temp, color, fd);
	return (color);
}
