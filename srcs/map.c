/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:38:23 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/08 01:19:09 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int is_map_line(char *line)
{
    while (*line == ' ')
        line++;
    return (*line == '1' || *line == '0');
}

char **get_map(char *path)
{
    int     fd;
    char    *line;
    char    **map;
    int     i = 0;
    int     map_started = 0;

    map = malloc(sizeof(char *) * 100);
    fd = open(path, O_RDONLY);

    while ((line = get_next_line(fd)))
    {
        if (!map_started)
        {
            if (is_map_line(line))
                map_started = 1;
            else
            {
                free(line);
                continue;
            }
        }
        map[i++] = ft_strtrim(line, "\n");
        free(line);
    }
    map[i] = NULL;
    close(fd);
    return (map);
}

void    draw_map(t_cub3d *game)
{
    char **map = game->map;
    int color = 0x0000FF;
    for (int y = 0; map[y]; y++)
        for (int x = 0; map[y][x]; x++)
        if (map[y][x] == '1')
            draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}

// char    **get_map(void)
// {
//     // char *line;
//     // int fd;

//     // get_next_line(fd);
//     char **map = malloc (sizeof(char *) * 15);
//     map[0] =  "11111111111111111111111111111111111111";
//     map[1] =  "10000000000000000001000000000000000001";
//     map[2] =  "10000000010000000001000000000000000101";
//     map[3] =  "10000000010000000001000000000000000101";
//     map[4] =  "10000000000000000001000000000000000101";
//     map[5] =  "10000000000000000000000000000000000101";
//     map[6] =  "10000000010000000001000000000000000101";
//     map[7] =  "10000000010000000001000000000000000101";
//     map[8] =  "10000000000000000001000000000000000001";
//     map[9] =  "10000000010000000001000000000000000101";
//     map[10] = "10000000000000000001000000000000000001";
//     map[11] = "10000000010000000001000000000000000101";
//     map[12] = "10000000000000000001000000000000000001";
//     map[13] = "11111111111111111111111111111111111111";
//     map[14] = NULL;
//     return (map);
// }
