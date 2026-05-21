/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 01:25:27 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/18 17:07:48 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	is_texture_identifier(char *line)
{
	return (!ft_strncmp(line, "NO", 2)
		|| !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2)
		|| !ft_strncmp(line, "EA", 2));
}

int	is_texture_line(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

static int	get_texture_index(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (0);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (2);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (3);
	return (-1);
}

int	extract_helper(t_cub3d *game, char *line)
{
	int		index;
	char	*names[4];

	names[0] = "NO";
	names[1] = "SO";
	names[2] = "WE";
	names[3] = "EA";
	index = 0;
	index = get_texture_index(line);
	if (index == -1)
		return (0);
	if (game->tex[index].img_path)
		return (printf("Duplicate %s texture\n", names[index]), 0);
	game->tex[index].img_path = extract_path(line);
	return (1);
}
