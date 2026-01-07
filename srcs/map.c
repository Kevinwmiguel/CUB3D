/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:38:23 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/06 18:07:26 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void    draw_map(t_cub3d *game)
{
    char **map = game->map;
    int color = 0x0000FF;
    for (int y = 0; map[y]; y++)
        for (int x = 0; map[y][x]; x++)
        if (map[y][x] == '1')
            draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}

char    **get_map(void)
{
    char **map = malloc (sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000000010001";
    map[6] = "100000000000001";
    map[7] = "101000000010001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}
