/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:38:23 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/09 18:17:47 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	draw_minimap_border(t_cub3d *game)
{
	int	x;
	int	y;
	int	left;
	int	top;

	left = WIDTH - MINIMAP_SIZE - MINIMAP_MARGIN;
	top = HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN;

	for (x = 0; x < MINIMAP_SIZE; x++)
	{
		put_pixel(left + x, top, 0x000000, game);
		put_pixel(left + x, top + MINIMAP_SIZE, 0x000000, game);
	}
	for (y = 0; y < MINIMAP_SIZE; y++)
	{
		put_pixel(left, top + y, 0x000000, game);
		put_pixel(left + MINIMAP_SIZE, top + y, 0x000000, game);
	}
}


void	cast_rays_3d(t_cub3d *game)
{
	float	ray_angle;
	float	step;
	int		i;

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


void	cast_rays_2d(t_cub3d *game)
{
	float	ray_angle;
	float	step;
	float	ray_x;
	float	ray_y;
	int		i;

	step = FOV / 120;
	ray_angle = game->player.angle - (FOV / 2);
	i = 0;

	while (i < 120)
	{
		ray_x = game->player.x;
		ray_y = game->player.y;

		while (!touch_wall(ray_x, ray_y, game))
		{
			put_pixel(
				ray_x - game->player.x + WIDTH / 2,
				ray_y - game->player.y + HEIGHT / 2,
				0xFF0000,
				game
			);
			ray_x += cos(ray_angle);
			ray_y += sin(ray_angle);
		}
		ray_angle += step;
		i++;
	}
}

void	cast_rays_minimap(t_cub3d *game)
{
	float	ray_angle;
	float	step;
	float	rx;
	float	ry;
	int		i;
	int		offset_x;
	int		offset_y;
	int		block;

	block = BLOCK * MINIMAP_SCALE;
	step = FOV / 60;
	ray_angle = game->player.angle - FOV / 2;
	i = 0;

	offset_x = WIDTH - (strlen(game->map[0]) * block) - MINIMAP_PADDING;
	offset_y = HEIGHT - (get_map_height(game->map) * block) - MINIMAP_PADDING;

	while (i < 60)
	{
		rx = game->player.x;
		ry = game->player.y;

		while (!touch_wall(rx, ry, game))
		{
			put_pixel(
				offset_x + (rx / BLOCK) * block,
				offset_y + (ry / BLOCK) * block,
				0xFF0000,
				game
			);
			rx += cos(ray_angle);
			ry += sin(ray_angle);
		}
		ray_angle += step;
		i++;
	}
}

// void	draw_player_minimap(t_cub3d *game)
// {
// 	int	block;
// 	int	x;
// 	int	y;
// 	block = BLOCK * MINIMAP_SCALE;
// 	x = WIDTH - (strlen(game->map[0]) * block)
// 		+ (game->player.x / BLOCK) * block
// 		- MINIMAP_PADDING;
// 	y = HEIGHT - (get_map_height(game->map) * block)
// 		+ (game->player.y / BLOCK) * block
// 		- MINIMAP_PADDING;
// 	draw_square(x, y, block / 2, 0x00FF00, game);
// }

void	draw_player_minimap(t_cub3d *game)
{
	int	cx;
	int	cy;

	cx = WIDTH - MINIMAP_SIZE / 2 - MINIMAP_MARGIN;
	cy = HEIGHT - MINIMAP_SIZE / 2 - MINIMAP_MARGIN;

	draw_square(cx - 3, cy - 3, 6, 0x00FF00, game);
}

int	get_map_height(char **map)
{
	int	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	draw_minimap(t_cub3d *game)
{
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;
	int	block;
	int	color;
	float	world_x;
	float	world_y;

	block = BLOCK * MINIMAP_SCALE;
	color = 0x888888;

	for (map_y = 0; game->map[map_y]; map_y++)
	{
		for (map_x = 0; game->map[map_y][map_x]; map_x++)
		{
			if (game->map[map_y][map_x] != '1')
				continue;

			/* posição do bloco no mundo */
			world_x = map_x * BLOCK;
			world_y = map_y * BLOCK;

			/* converte mundo → minimapa (player centralizado) */
			screen_x = WIDTH - MINIMAP_SIZE - MINIMAP_MARGIN
				+ (world_x - game->player.x) * MINIMAP_SCALE
				+ MINIMAP_SIZE / 2;

			screen_y = HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN
				+ (world_y - game->player.y) * MINIMAP_SCALE
				+ MINIMAP_SIZE / 2;

			/* recorte da janela do minimapa */
			if (screen_x < WIDTH - MINIMAP_SIZE - MINIMAP_MARGIN
				|| screen_x > WIDTH - MINIMAP_MARGIN
				|| screen_y < HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN
				|| screen_y > HEIGHT - MINIMAP_MARGIN)
				continue;

			draw_square(screen_x, screen_y, block, color, game);
		}
	}
}


// void	draw_minimap(t_cub3d *game)
// {
// 	int	x;
// 	int	y;
// 	int	screen_x;
// 	int	screen_y;
// 	int	block;
// 	int	color;

// 	block = BLOCK * MINIMAP_SCALE;
// 	color = 0xAAAAAA;

// 	for (y = 0; game->map[y]; y++)
// 	{
// 		for (x = 0; game->map[y][x]; x++)
// 		{
// 			if (game->map[y][x] == '1')
// 			{
// 				screen_x = WIDTH - (strlen(game->map[y]) * block)
// 					+ x * block - MINIMAP_PADDING;
// 				screen_y = HEIGHT - (get_map_height(game->map) * block)
// 					+ y * block - MINIMAP_PADDING;

// 				draw_square(screen_x, screen_y, block, color, game);
// 			}
// 		}
// 	}
// }

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

void	draw_map(t_cub3d *game)
{
	int		x;
	int		y;
	int		screen_x;
	int		screen_y;
	int		color = 0xFF00FF;

	for (y = 0; game->map[y]; y++)
	{
		for (x = 0; game->map[y][x]; x++)
		{
			if (game->map[y][x] == '1')
			{
				screen_x = x * BLOCK - game->player.x + WIDTH / 2;
				screen_y = y * BLOCK - game->player.y + HEIGHT / 2;

				if (screen_x + BLOCK < 0 || screen_x > WIDTH)
					continue;
				if (screen_y + BLOCK < 0 || screen_y > HEIGHT)
					continue;

				draw_square(screen_x, screen_y, BLOCK, color, game);
			}
		}
	}
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
