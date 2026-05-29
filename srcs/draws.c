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

static int	process_texture_line(t_cub3d *game, char *line, int fd)
{
	line = skip_spaces(line);
	if (is_texture_identifier(line) && !is_texture_line(line))
	{
		printf("Error\nInvalid texture line\n");
		free(line);
		close(fd);
		destroy_game(game, 0);
		return (0);
	}
	if (is_texture_line(line))
	{
		if (!extract_helper(game, line))
		{
			free(line);
			close(fd);
			destroy_game(game, 1);
		}
	}
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
		if (!process_texture_line(game, line, fd))
			return ;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
