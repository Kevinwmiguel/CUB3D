/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:15:38 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/08 20:57:10 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define WIDTH 1920
# define HEIGHT 1080
# define BLOCK 64
# define DEBUG 0
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define PI 3.14159265359
# define PLAYER_RADIUS 4
# define ESC 65307

# define PRT_NORTH "NO"
# define PRT_SOUTH "SO"
# define PRT_EAST "EA"
# define PRT_WEST "WE"
# define PRT_FLOOR "F"
# define PRT_CEIL "C"
# define PRT_DOOR "DO"
# define PRT_SPR "SP"

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../includes/minilibx-linux/mlx.h"
# include <stdio.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_cub3d
{
	void			*mlx;
	void			*win;
	char			*ceiling;
	char			*floor;
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	t_player		player;
	char			**map;
}	t_cub3d;


void ft_free_split(char **s);
void parse_colors(t_cub3d *game, char *path);
void	put_pixel(int x, int y, int color, t_cub3d *game);
void paint_floor_and_ceiling(t_cub3d *game);
int hex_to_int(const char *hex);
void	init_player(t_player *player);
void	draw_square(int x, int y, int size, int color, t_cub3d *game);
int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
void	move_player(t_player *player, t_cub3d *game);
int		draw_loop(t_cub3d *game);
char    **get_map(char *path);
void    draw_map(t_cub3d *game);

#endif