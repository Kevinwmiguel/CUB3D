/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:52:14 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/08 20:52:21 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char *process_rgb_line(char *line)
{
    char **tab;
    char **rgb;
    char *r_hex; char *g_hex; char *b_hex;
    char *tmp; char *final_hex;

    tab = ft_split(line, ' ');
    if (!tab || !tab[1]) return (NULL);
    
    rgb = ft_split(tab[1], ',');
    ft_free_split(tab);
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
    {
        ft_free_split(rgb);
        return (NULL);
    }
    
    r_hex = ft_int_to_hex(ft_atoi(rgb[0]));
    g_hex = ft_int_to_hex(ft_atoi(rgb[1]));
    b_hex = ft_int_to_hex(ft_atoi(rgb[2]));
    ft_free_split(rgb);

    tmp = ft_strjoin(r_hex, g_hex);
    final_hex = ft_strjoin(tmp, b_hex);
    
    free(r_hex); free(g_hex); free(b_hex); free(tmp);
    return (final_hex);
}

void parse_colors(t_cub3d *game, char *path)
{
    int     fd;
    char    *line;

    fd = open(path, O_RDONLY);
    if (fd < 0) return ;

    while ((line = get_next_line(fd)))
    {
        // Ignora espaços vazios no início da linha se necessário
        if (line[0] == 'F' && line[1] == ' ')
            game->floor = process_rgb_line(line);
        else if (line[0] == 'C' && line[1] == ' ')
            game->ceiling = process_rgb_line(line);
        
        free(line);
        // Se já pegou as duas, podes dar break ou continuar para ler o mapa
        if (game->floor && game->ceiling)
            break;
    }
    
    // IMPORTANTE: Limpar o resto do GNL para não deixar leaks ou lixo no buffer
    while ((line = get_next_line(fd)))
        free(line);
    close(fd);
}