/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:15:38 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/18 16:23:36 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DOIS PROBLEMAS
// RAYCASTING N ESTA ALINHADO
// 2D E 3D APARECEM EM SIMULTANEO

#ifndef GAME_H
# define GAME_H

# define WIDTH 1080
# define HEIGHT 720
# define BLOCK 64
# define MINIMAP_PADDING 20
# define MINIMAP_SIZE 180
# define MINIMAP_SCALE 0.2
# define MINIMAP_MARGIN 20
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
	int			width;
	int			height;
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

typedef struct s_hit
{
	float	wall_x;
	int		side;
	int		tex_id;
}			t_hit;

typedef struct s_wall
{
	t_texture	*tex;
	int			tex_x;
	int			tex_y;
	float		wall_height;
	float		step;
	float		tex_pos;
}				t_wall;

typedef struct s_wcol
{
	int		col;
	int		start;
	int		end;
	float	dist;
}			t_wcol;

typedef struct s_rayhit
{
	float	prev_x;
	float	prev_y;
	float	step_x;
	float	step_y;
}				t_rayhit;

typedef struct s_dda
{
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	float	perp_wall_dist;
}			t_dda;

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
	float		fov;
	t_hit		hit;
	t_rayhit	ray_hit;
	char		*line;
	char		color_letter;
}				t_cub3d;

int				is_valid_wall(char c);
int				is_walkable(char c);
int				valid_elements(char c);
int				check_rgb_format(char *line);
void			clean_newline(char *str);
int				check_englobe(char *current, char *prev, char *next);
float			distance(float x, float y);
void			ready_go(t_cub3d *game);
int				init_cub3d(t_cub3d *game, char *path);
char			*fc_help(t_cub3d *game, char **temp, char *color, int fd);
int				hex_to_int(const char *hex);
char			*get_ceiling(t_cub3d *game, char *path);
char			*build_color(char **temp2);
char			*get_floor(t_cub3d *game, char *path);
int				destroy_game(t_cub3d *game, int flag);
void			render_rays(t_cub3d *game);
void			fcleaner(t_cub3d *game);
void			free_textures_ceiling(t_cub3d *game);
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
void			draw_minimap(t_cub3d *game);
void			cast_rays(t_cub3d *game);
void			set_player_from_map(t_cub3d *game);
void			draw_line(t_cub3d *g, float angle, int col);
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
void			draw_player(t_cub3d *game);
int				check_map_name(char *av);
float			trace_ray_dda(t_cub3d *game, float angle);
int				perform_dda(t_dda *dda, t_cub3d *game);
void			init_dda(t_dda *dda, t_player *player, float ray_angle);
void			calculate_map_dimensions(t_cub3d *game);
int				is_map_start(char *line);
int				is_texture_or_color(char *line);
int				is_empty_line(char *line);
int				handle_color_line(char *line, int *f, int *c);
int				validate_config_line(char *line, int *f, int *c);
int				precheck_colors(char *path);
int				is_texture_identifier(char *line);
int				is_texture_line(char *line);
int				extract_helper(t_cub3d *game, char *line);
char			*extract_path(char *line);
int				count_lines(char *path);

#endif