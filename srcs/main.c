/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:15:43 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/13 23:40:47 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	render_rays(t_cub3d *game)
{
	int		i;
	float	ray_angle;
	float	fov;
	float	step;

	fov = PI / 3;
	step = fov / WIDTH;
	ray_angle = game->player.angle - (fov / 2);
	i = 0;
	while (i < WIDTH)
	{
		draw_line(&game->player, game, ray_angle, i);
		ray_angle += step;
		i++;
	}
}

int	hex_to_int(const char *hex)
{
	char	tmp[3];

	int r, g, b;
	if (ft_strlen(hex) != 6)
		return (0x000000); // preto se inválido
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

void	paint_floor_and_ceiling(t_cub3d *game)
{
	int	color_floor;
	int	color_ceiling;
	int	*pixels;

	int x, y;
	color_floor = hex_to_int(game->floor);
	color_ceiling = hex_to_int(game->ceiling);
	pixels = (int *)game->data;
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
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
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
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0, game);
}

void	ft_free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	*get_floor(char *path)
{
	int		fd;
	char	*line;
	char	**temp;
	char	**temp2;
	char	*fixedcolor;
	char	*r;
	char	*g;
	char	*b;
	char	*tmp_join;

	fixedcolor = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == 'F' && line[1] == ' ')
		{
			temp = ft_split(line, ' ');
			if (temp && temp[1])
			{
				temp2 = ft_split(temp[1], ',');
				if (temp2 && temp2[0] && temp2[1] && temp2[2])
				{
					r = ft_int_to_hex(ft_atoi(temp2[0]));
					g = ft_int_to_hex(ft_atoi(temp2[1]));
					b = ft_int_to_hex(ft_atoi(temp2[2]));
					tmp_join = ft_strjoin(r, g);
					fixedcolor = ft_strjoin(tmp_join, b);
					free(r);
					free(g);
					free(b);
					free(tmp_join);
				}
				ft_free_split(temp2);
			}
			ft_free_split(temp);
			free(line);
			break ;
		}
		free(line);
	}
	while ((line = get_next_line(fd)))
		free(line);
	close(fd);
	return (fixedcolor);
}

char	*get_ceiling(char *path)
{
	int		fd;
	char	*line;
	char	**temp;
	char	**temp2;
	char	*fixedcolor;
	char	*r;
	char	*g;
	char	*b;
	char	*tmp_join;

	fixedcolor = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == 'C' && line[1] == ' ')
		{
			temp = ft_split(line, ' ');
			if (temp && temp[1])
			{
				temp2 = ft_split(temp[1], ',');
				if (temp2 && temp2[0] && temp2[1] && temp2[2])
				{
					r = ft_int_to_hex(ft_atoi(temp2[0]));
					g = ft_int_to_hex(ft_atoi(temp2[1]));
					b = ft_int_to_hex(ft_atoi(temp2[2]));
					tmp_join = ft_strjoin(r, g);
					fixedcolor = ft_strjoin(tmp_join, b);
					free(r);
					free(g);
					free(b);
					free(tmp_join);
				}
				ft_free_split(temp2);
			}
			ft_free_split(temp);
			free(line);
			break ;
		}
		free(line);
	}
	while ((line = get_next_line(fd)))
		free(line);
	close(fd);
	return (fixedcolor);
}

void	init_cub3d(t_cub3d *game, char *path)
{
	init_player(&game->player);
	game->tab = NULL;
	game->rgb = NULL;
	game->r_hex = NULL;
	game->g_hex = NULL;
	game->b_hex = NULL;
	game->tmp = NULL;
	game->final_hex = NULL;
	get_textures(game, path);
	game->floor = get_floor(path);
	game->ceiling = get_ceiling(path);
	parse_colors(game, path);
	if (!game->floor || !game->ceiling)
		printf("Erro: Cores não encontradas ou mal formatadas!\n");
	game->map = get_map(path);
	if (!validate_map(game->map))
	{
		printf("Mapa inválido\n");
		/* aqui você faz o que quiser */
		exit(1);
	}
	set_player_from_map(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Imersive");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

bool	touch(float px, float py, t_cub3d *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_cub3d *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_line(t_player *player, t_cub3d *game, float ray_angle, int column)
{
	float	ray_x;
	float	ray_y;
	float	step_x;
	float	step_y;
	int		screen_x;
	int		screen_y;
	float	dist;
	float	wall_height;
	int		start;
	int		end;

	ray_x = player->x;
	ray_y = player->y;
	step_x = cos(ray_angle);
	step_y = sin(ray_angle);
	while (!touch_wall(ray_x, ray_y, game))
	{
		if (DEBUG)
		{
			screen_x = ray_x - player->x + WIDTH / 2;
			screen_y = ray_y - player->y + HEIGHT / 2;
			put_pixel(screen_x, screen_y, 0xFFFF00, game);
		}
		ray_x += step_x;
		ray_y += step_y;
	}
	if (!DEBUG)
	{
		dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
		wall_height = (BLOCK / dist) * (WIDTH / 2);
		start = (HEIGHT / 2) - (wall_height / 2);
		end = (HEIGHT / 2) + (wall_height / 2);
		if (start < 0)
			start = 0;
		if (end > HEIGHT)
			end = HEIGHT;
		while (start < end)
		{
			put_pixel(column, start, 0xE10AFF, game);
			start++;
		}
	}
}

void	draw_player(t_cub3d *game)
{
	int	cx;
	int	cy;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	draw_square(cx - 15, cy - 15, 10, 0x00FF00, game);
}

int	draw_loop(t_cub3d *game)
{
	move_player(&game->player, game);
	clear_image(game);
	paint_floor_and_ceiling(game);
	if (DEBUG)
	{
		draw_map(game);
		draw_player(game);
		cast_rays_2d(game);
	}
	else
	{
		cast_rays_3d(game);
		draw_minimap(game);
		draw_player_minimap(game);
		draw_minimap_border(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	fechar_janela(void *param)
{
	// Vou por um cleaner aqui
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
		mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
		mlx_hook(game.win, 17, 0, fechar_janela, NULL);
		mlx_loop_hook(game.mlx, draw_loop, &game);
		mlx_loop(game.mlx);
	}
	return (0);
}
