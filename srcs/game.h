/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:15:38 by kwillian          #+#    #+#             */
/*   Updated: 2026/02/09 00:57:20 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DOIS PROBLEMAS
// RAYCASTING N ESTA ALINHADO
// 2D E 3D APARECEM EM SIMULTANEO

#ifndef GAME_H
# define GAME_H

# define WIDTH 1920
# define HEIGHT 1080
# define BLOCK 64
# define MINIMAP_PADDING 20
# define MINIMAP_SIZE 180
# define MINIMAP_SCALE 0.2
# define MINIMAP_MARGIN 20
# define DEBUG 0
# define FOV (PI / 3)
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define PI 3.14159265359
# define PLAYER_RADIUS 4
# define ESC 65307

# include "../get_next_line/get_next_line.h"
# include "../includes/minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_texture
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*type;
	char		*img_path;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;
	float		speed;
	float		angle_speed;
	float		cos_angle;
	float		sin_angle;
	float		next_x;
	float		next_y;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		left_rotate;
	bool		right_rotate;
}				t_player;

typedef struct s_configs
{
	float		ray_angle;
	float		step;
	float		rx;
	float		ry;
	int			i;
	int			offset_x;
	int			offset_y;
	int			block;
}				t_configs;

typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	char		*ceiling;
	char		*floor;
	void		*img;
	char		*data;
	t_texture	tex[4];
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	t_configs	raycaster;
	char		**map;
	char		**tab;
	char		**rgb;
	char		*r_hex;
	char		*g_hex;
	char		*b_hex;
	char		*tmp;
	char		*final_hex;
	int			x_map;
	int			y_map;
	int			draw_count;
	int			colorhelp;
	float		x1;
	float		y1;
	float		x2;
	float		y2;
}				t_cub3d;

float			fixed_dist(t_cub3d *game);
int				hex_to_int(const char *hex);
char			*get_ceiling(char *path);
char			*get_floor(char *path);
int				destroy_game(t_cub3d *game);
void			render_rays(t_cub3d *game);
void			fcleaner(t_cub3d *game);
bool			is_player_char(char c);
bool			is_map_char(char c);
bool			validate_map(t_cub3d *game, char **map);
void			cast_rays_2d(t_cub3d *game);
void			cast_rays_3d(t_cub3d *game);
void			draw_minimap(t_cub3d *game);
int				get_map_height(char **map);
void			draw_player_minimap(t_cub3d *game);
void			draw_minimap_border(t_cub3d *game);
void			cast_rays_2d(t_cub3d *game);
void			cast_rays_3d(t_cub3d *game);
void			draw_player_minimap(t_cub3d *game);
int				get_map_height(char **map);
void			draw_minimap(t_cub3d *game);
void			cast_rays(t_cub3d *game);
void			set_player_from_map(t_cub3d *game);
void			draw_line(t_player *p, t_cub3d *g, float angle, int col);
bool			touch_wall(float px, float py, t_cub3d *game);
void			ft_free_split(char **s);
void			parse_colors(t_cub3d *game, char *path);
void			put_pixel(int x, int y, int color, t_cub3d *game);
void			paint_floor_and_ceiling(t_cub3d *game);
int				hex_to_int(const char *hex);
void			init_player(t_player *player);
void			draw_square(int x, int y, int size, t_cub3d *game);
int				key_press(int keycode, t_cub3d *game);
int				key_release(int keycode, t_cub3d *game);
void			move_player(t_player *player, t_cub3d *game);
int				draw_loop(t_cub3d *game);
char			**get_map(char *path);
void			draw_map(t_cub3d *game);
void			get_textures(t_cub3d *game, char *path);
void			draw_minimap_border(t_cub3d *game);
void			exit_clean(t_cub3d *game);
void			clear_image(t_cub3d *game);
void			put_pixel(int x, int y, int color, t_cub3d *game);
void			paint_floor_and_ceiling(t_cub3d *game);
int				draw_loop(t_cub3d *game);
void			draw_player(t_cub3d *game);

#endif