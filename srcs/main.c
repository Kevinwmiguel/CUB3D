/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:15:43 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/09 02:52:21 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int hex_to_int(const char *hex)
{
    int r, g, b;

    if (ft_strlen(hex) != 6)
        return (0xA8F2B4); // preto se inválido

    char tmp[3];
    tmp[2] = '\0';

    tmp[0] = hex[0];
    tmp[1] = hex[1];
    r = (int)strtol(tmp, NULL, 16);

    tmp[0] = hex[2];
    tmp[1] = hex[3];
    g = (int)strtol(tmp, NULL, 16);

    tmp[0] = hex[4];
    tmp[1] = hex[5];
    b = (int)strtol(tmp, NULL, 16);

    return (r << 16 | g << 8 | b);
}

void paint_floor_and_ceiling(t_cub3d *game)
{
    int x, y;
    int color_floor = hex_to_int(game->floor);
    int color_ceiling = hex_to_int(game->ceiling);

    int *pixels = (int *)game->data;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            if (y < HEIGHT / 2)
                pixels[y * (game->size_line / 4) + x] = color_ceiling;
            else
                pixels[y * (game->size_line / 4) + x] = color_floor;
        }
    }
}


void	put_pixel(int x, int y, int color, t_cub3d *game)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;

	int index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
	
}

void	draw_square(int x, int y, int size, int color, t_cub3d *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + size, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y + size, color, game);
		i++;
	}
}

void	clear_image(t_cub3d *game)
{
	for(int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			put_pixel(x,y, 0, game);
}


void ft_free_split(char **s)
{
	int i = 0;
	while (s[i])
	free(s[i++]);
	free(s);
}

char *get_floor(char *path)
{
	int		fd;
	char	*line;
	char	**temp;
	char	**temp2;
	int		r, g, b;
	char	*red;
	char	*green;
	char	*blue;
	char	*tmp;
	char	*fixedcolor;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == 'F' && line[1] == ' ')
			break;
		free(line);
	}
	close(fd);
	if (!line)
		return (NULL);
	temp = ft_split(line, ' ');
	free(line);
	if (!temp || !temp[1])
		return (NULL);
	temp2 = ft_split(temp[1], ',');
	ft_free_split(temp);
	if (!temp2 || !temp2[0] || !temp2[1] || !temp2[2])
		return (NULL);
	r = ft_atoi(temp2[0]);
	g = ft_atoi(temp2[1]);
	b = ft_atoi(temp2[2]);
	printf("red como R %d\n\n", r);
	printf("green como g %d\n\n", g);
	printf("blue como b %d\n\n", b);
	ft_free_split(temp2);
	red = ft_int_to_hex(r);
	green = ft_int_to_hex(g);
	blue = ft_int_to_hex(b);
	tmp = ft_strjoin(red, green);
	
	printf("red %s\n", red);
	printf("green %s\n", green);
	printf("blue %s\n", blue);
	fixedcolor = ft_strjoin(tmp, blue);

	free(red);
	free(green);
	free(blue);
	free(tmp);
	printf("color fixed %s\n", fixedcolor);
	close(fd);
	return (fixedcolor);	
}

char *get_ceiling(char *path)
{
	int		fd;
	char	*line;
	char	**temp;
	char	**temp2;
	int		r, g, b;
	char	*red;
	char	*green;
	char	*blue;
	char	*tmp;
	char	*fixedcolor;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == 'C' && line[1] == ' ')
			break;
		free(line);
	}
	close(fd);
	if (!line)
		return (NULL);
	temp = ft_split(line, ' ');
	free(line);
	if (!temp || !temp[1])
		return (NULL);
	temp2 = ft_split(temp[1], ',');
	ft_free_split(temp);
	if (!temp2 || !temp2[0] || !temp2[1] || !temp2[2])
		return (NULL);
	r = ft_atoi(temp2[0]);
	g = ft_atoi(temp2[1]);
	b = ft_atoi(temp2[2]);
	printf("red como R %d\n\n", r);
	printf("green como g %d\n\n", g);
	printf("blue como b %d\n\n", b);
	ft_free_split(temp2);
	red = ft_int_to_hex(r);
	green = ft_int_to_hex(g);
	blue = ft_int_to_hex(b);
	tmp = ft_strjoin(red, green);
	printf("red %s\n", red);
	printf("green %s\n", green);
	printf("blue %s\n", blue);
	fixedcolor = ft_strjoin(tmp, blue);
	free(red);
	free(green);
	free(blue);
	free(tmp);
	printf("color fixed %s\n", fixedcolor);
	return (fixedcolor);
}

// char *get_ceiling(char *path)
// {
//     int     fd;
//     char    *line;
//     char    **temp;
//     char    **temp2;
//     char    *fixedcolor = NULL;
//
//     fd = open(path, O_RDONLY);
//     if (fd < 0) return (NULL);
//
//     while ((line = get_next_line(fd)))
//     {
//         // Trim no line aqui se necessário para remover o \n
//         if (line[0] == 'C' && line[1] == ' ')
//         {
//             temp = ft_split(line, ' ');
//             if (temp && temp[1])
//             {
//                 temp2 = ft_split(temp[1], ',');
//                 // VERIFICAÇÃO CRÍTICA: Se r, g e b existem
//                 if (temp2 && temp2[0] && temp2[1] && temp2[2])
//                 {
//                     char *r = ft_int_to_hex(ft_atoi(temp2[0]));
//                     char *g = ft_int_to_hex(ft_atoi(temp2[1]));
//                     char *b = ft_int_to_hex(ft_atoi(temp2[2]));
//                  
//                     char *tmp_join = ft_strjoin(r, g);
//                     fixedcolor = ft_strjoin(tmp_join, b);
//                  
//                     free(r); free(g); free(b); free(tmp_join);
//                 }
//                 ft_free_split(temp2);
//             }
//             ft_free_split(temp);
//             free(line); // Importante: limpa a linha onde achou o 'C'
//             break; // Sai do loop mal encontre
//         }
//         free(line);
//     }
//     // Limpeza final do GNL (importante para não dar segfault na próxima leitura)
//     while ((line = get_next_line(fd))) 
//         free(line);
//     close(fd);
//     return (fixedcolor);
// }

void	init_cub3d(t_cub3d *game, char *path)
{
	
	printf("path %s\n", path);
	init_player(&game->player);
	get_textures(game, path);
	printf("north %s\n", game->tex[0].img_path);
	printf("South %s\n", game->tex[1].img_path);
	printf("Weast %s\n", game->tex[2].img_path);
	printf("East %s\n", game->tex[3].img_path);
	exit(1);
	// game->floor = get_floor(path);
	// printf("floor %s\n", game->floor);
	// game->ceiling = get_ceiling(path);
	// printf("\nceiling %s\n", game->ceiling);
	parse_colors(game, path);
    if (!game->floor || !game->ceiling)
	{
        printf("Erro: Cores não encontradas ou mal formatadas!\n");
	}
	game->map = get_map(path);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "FLYING WATERS");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0,0);
}

bool	touch(float px, float py, t_cub3d *game)
{
	int x = px / BLOCK;
	int y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1,float x2, float y2, t_cub3d *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_line(t_player *player, t_cub3d *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;

	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0xE10AFF,game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBUG)
	{
		float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
		float height = (BLOCK / dist) * (WIDTH / 2);
		int start_y = (HEIGHT - height) / 2;
		int end = start_y + height;
		while (start_y < end)
		{
			put_pixel(i, start_y, 0xE10AFF, game);
			start_y++;
		}
	}
}

int	draw_loop(t_cub3d *game)
{
	t_player	*player = &game->player;
	move_player(player, game);
	clear_image(game);
	paint_floor_and_ceiling(game);
	if (DEBUG)
	{
		draw_square(player->x, player->y, 15, 0x00FF00, game);
		draw_map(game);
	}
	float fraction = PI / 3 / WIDTH;
	float start_x = player->angle - PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int fechar_janela(void *param)
{
    //Vou por um cleaner aqui
    (void)param;
    exit(0);
    return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	game;
	if (argc == 2)
	{
		init_cub3d(&game, argv[1]);	
		mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
		mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
		mlx_hook(game.win, 17, 0, fechar_janela, NULL);
		mlx_loop_hook(game.mlx, draw_loop, &game);
		mlx_loop(game.mlx);
	}
	return (0);
}
