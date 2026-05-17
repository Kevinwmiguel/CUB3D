/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 01:25:27 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/17 23:08:12 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char	*extract_path(char *line)
{
	char	*path;
	int		i;

	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	path = ft_strdup(&line[i]);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i] && path[i] != '\n')
		i++;
	path[i] = '\0';
	return (path);
}

void	clean_line(int count, char *line, int fd)
{
	while (count > 0)
	{
		line = get_next_line(fd);
		free(line);
		count--;
	}
}

int	is_texture_line(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

int	extract_helper(t_cub3d *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->tex[0].img_path = extract_path(line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->tex[1].img_path = extract_path(line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->tex[2].img_path = extract_path(line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->tex[3].img_path = extract_path(line);
	else
		return (0);
	return (1);
}

void	get_textures(t_cub3d *game, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		if (is_texture_line(line))
		{
			if (!extract_helper(game, line))
			{
				free(line);
				close(fd);
				destroy_game(game, 1);
			}
		}
		free(line);
		if (game->tex[0].img_path && game->tex[1].img_path
			&& game->tex[2].img_path && game->tex[3].img_path)
			break ;
		line = get_next_line(fd);
	}
	close(fd);
}
