/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 01:25:27 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/31 18:33:52 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	cast_rays(t_cub3d *game)
{
	int		i;
	float	ray_angle;
	float	step;

	step = FOV / WIDTH;
	ray_angle = game->player.angle - (FOV / 2);
	i = 0;
	while (i < WIDTH)
	{
		draw_line(&game->player, game, ray_angle, i);
		ray_angle += step;
		i++;
	}
}

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

void	extract_helper(t_cub3d *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->tex[0].img_path = extract_path(line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->tex[1].img_path = extract_path(line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->tex[2].img_path = extract_path(line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->tex[3].img_path = extract_path(line);
}

void	get_textures(t_cub3d *game, char *path)
{
	int		fd;
	char	*line;
	int		j;

	j = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		j++;
		extract_helper(game, line);
		free(line);
		if (game->tex[0].img_path && game->tex[1].img_path
			&& game->tex[2].img_path && game->tex[3].img_path)
			break ;
		line = get_next_line(fd);
	}
	clean_line(j, line, fd);
	close(fd);
}
