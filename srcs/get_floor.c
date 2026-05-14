/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:56:40 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/14 17:40:47 by kwillian         ###   ########.fr       */
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

char	*get_floor(t_cub3d *game,char *path)
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
	game->color_letter = 'F';
	color = fc_help(game, temp, color, fd);
	return (color);
}
