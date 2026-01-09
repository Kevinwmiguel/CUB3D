/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 01:25:27 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/09 17:59:45 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//mlx_put_image_to_window(game->mlx, game->win, game->assets->water->img, x1, y1);
//Walls aqui

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

	i = 2; // Pula 'NO', 'SO', etc.
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	path = ft_strdup(&line[i]);
	if (!path)
		return (NULL);
	// Remove o \n no final, se existir
	i = 0;
	while (path[i] && path[i] != '\n')
		i++;
	path[i] = '\0';
	return (path);
}


void    get_textures(t_cub3d *game, char *path)
{
    int     fd;
    char    *line;

    fd = open(path, O_RDONLY);
    if (fd < 0) return ;
    while ((line = get_next_line(fd)))
    {
        if (ft_strncmp(line, "NO ", 3) == 0)
            game->tex[0].img_path = extract_path(line);
        else if (ft_strncmp(line, "SO ", 3) == 0)
            game->tex[1].img_path = extract_path(line);
        else if (ft_strncmp(line, "WE ", 3) == 0)
            game->tex[2].img_path = extract_path(line);
        else if (ft_strncmp(line, "EA ", 3) == 0)
            game->tex[3].img_path = extract_path(line);
        free(line);
        // Verifica se já pegou as 4 texturas para parar cedo
        if (game->tex[0].img_path && game->tex[1].img_path && 
            game->tex[2].img_path && game->tex[3].img_path)
            break;
    }
    // Limpa o resto do FD para evitar leaks do GNL
    while ((line = get_next_line(fd)))
        free(line);
    close(fd);
}

// Exemplo genérico para carregar a imagem
// game->tex[i].img = mlx_xpm_file_to_image(game->mlx, game->tex[i].img_path, &width, &height);
// game->tex[i].data = mlx_get_data_addr(game->tex[i].img, &game->tex[i].bpp, &game->tex[i].size_line, &game->tex[i].endian);

//Proteção: Se o mlx_xpm_file_to_image falhar (devolver NULL), fechar o programa com uma mensagem de erro "Error\nInvalid texture path".
//Leaks: Lembra-te de dar free nos img_path e mlx_destroy_image ao fechar o jogo.


//funcao mestra

// void parse_file(t_cub3d *game, char *path)
// {
//     int fd = open(path, O_RDONLY);
//     char *line;

//     while ((line = get_next_line(fd)))
//     {
//         if (is_texture_line(line))
//             save_texture(game, line);
//         else if (is_color_line(line))
//             save_color(game, line);
//         else if (is_map_start(line))
//         {
//             // Quando chega ao mapa, podes chamar a função do mapa
//             // e passar o FD para ela continuar a ler dali
//             parse_map(game, line, fd); 
//             break; // O parse_map vai ler até ao fim
//         }
//         free(line);
//     }
//     close(fd);
// }
