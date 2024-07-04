/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:55:41 by gsapio            #+#    #+#             */
/*   Updated: 2024/07/04 18:20:09 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx-linux/mlx.h"
# include "Libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define TEXTURE_DIM 64
# define TILE_DIM 64.0
# define MAP_TILE_DIM 8
# define PLAYER_DIM 2
# define VELOCITY 8
# define PI 3.14159265359
# define PI_2 1.570796326795
# define PI_3 4.712388980385001
# define DGR 0.0174533
# define VIEWPORT_W 960
# define VIEWPORT_H 540
# define MAX_DOF 40

typedef struct s_v2
{
	int			x;
	int			y;
	float		angle;
}				t_v2;

typedef struct s_f_v2
{
	float		fx;
	float		fy;
	float		angle;
}				t_f_v2;

typedef struct s_image
{
	void		*img_ptr;
	int			i_height;
	int			i_width;
	int			pixel_bits;
	int			line_bytes;
	int			endian;
	char		*buffer;
}				t_image;

typedef struct s_ray_vars
{
	int			dof;
	t_f_v2		ray;
	t_f_v2		off;
}				t_ray_vars;

typedef struct s_keycub
{
	int			w;
	int			n;
	int			s;
	int			e;
	int			f;
	int			c;
}				t_keycub;

typedef struct s_line
{
	int			x;
	int			y;
	int			y0;
	int			y1;
	int			tex_x;
	int			tex_y;
}				t_line;

typedef struct s_texture
{
	float		ty;
	float		ty_step;
	float		ty_off;
	float		tx;
}				t_texture;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
	char		**map;
	t_image		images[4];
	int			floor_color;
	int			ceiling_color;
	float		render_flag;
	t_v2		pos;
	t_v2		pos_handle;
	t_v2		dir;
	t_ray_vars	ray_v;
	t_ray_vars	ray_h;
	float		dist_h;
	float		dist_v;
	float		dist_t;
	float		prev_dist_v;
	float		prev_dist_h;
	float		limit_dof;
	t_image		ceil_floor;
	t_image		walls;
	t_image		walls_image;
	t_keycub	keys;
	t_v2		int_ray;
	int			mouse_down;
	int			max_dof_f;
}				t_mlx;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

int				parse_file(int argc, char **argv, t_mlx *mlx);

// bit_colors
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);

// Utils
void			init_elements(t_mlx *mlx);
int				destroy_game(t_mlx *mlx);
int				destroy_game_on_start(t_mlx *mlx);
int				error_fclose(int *fd);
void			count_cols_rows(int *i, int *j, char **map);
int				wall_index(t_mlx *mlx);
void			find_player_in_map(char **map, int *i, int *j, t_v2 *vector);
t_v2			player_pos(t_mlx *mlx);
int				wall_index(t_mlx *mlx);
void			make_wall_in_image(t_mlx *mlx, int x, int y, t_texture tex);
void			check_distance(t_mlx *mlx);
void			map_pos(t_mlx *mlx, int mode);
int				float_comp_conditional(t_mlx *mlx, t_ray_vars *ray);
void			clean_gnl(char *tstr, int *fd);

/* Parsing */
int				check_all_elements(t_mlx *mlx);
void			set_color(char *str, int *color);
void			set_image(char *str, t_image *image, t_mlx *mlx);
int				get_elements(char *str, t_mlx *mlx);
int				check_elements(int fd, char **argv, t_mlx *mlx);
int				skip_spaces(char *str);
int				valid_chars(char tile);
int				valid_tile(char **map, int i, int j);
int				valid_player(char tile);
int				map_manager(int fd, char **argv, t_mlx *mlx);

// graphics
void			dda(t_v2 vec0, t_v2 vec1, int color, t_mlx *mlx);
int				draw_map(t_mlx *mlx);
int				draw_player_loop(t_mlx *mlx);
int				draw_player_iterative(t_mlx *mlx);
void			draw_tile(int color, int i, int j, t_mlx *mlx);
void			reset_buffer(t_mlx *mlx);
t_v2			player_pos(t_mlx *mlx);
void			find_player_in_map(char **map, int *i, int *j, t_v2 *vector);
void			empty_buffer(t_mlx *mlx);
void			put_color_to_pixel(int *yx, char *buffer, int color,
					t_mlx *mlx);
void			put_color_to_wall(t_mlx *mlx, int *yx, char *buffer[2],
					int ind[2]);
int				draw_minimap(t_mlx *mlx);

// movement
void			on_move(t_mlx *mlx, int keycode, float pdy, float pdx);
void			on_rotate(t_mlx *mlx, int keycode);
void			compute_direction(t_mlx *mlx, float *pdx, float *pdy);

/* Ray Casting*/
int				casting_rays_horizontal(t_mlx *mlx, int tile_dim);
void			casting_rays(int *count, t_mlx *mlx, int tile_dim);
int				casting_rays_vertical(t_mlx *mlx, int tile_dim);
void			set_ray_coordinates_v(t_mlx *mlx, float nTan, float pi_2,
					int tile_dim);
void			set_v_ray(t_mlx *mlx, int tile_dim);
int				float_comp(float first, float second);
void			set_ray_coordinates_h(t_mlx *mlx, float coTan, int tile_dim);
void			set_h_ray(t_mlx *mlx, int tile_dim);
int				draw_walls(t_mlx *mlx);
float			dist(t_v2 player, t_f_v2 ray);
int				re_calculate_ray(t_mlx *mlx, t_v2 *m, int cols_rows[2]);
void			set_limit_dof(int cols_rows[2], t_mlx *mlx);
int				raycast_vertical_loop(t_mlx *mlx, t_v2 m, int nrows, int ncols);
int				ray_vertical_recalculate(t_v2 *m, int cols_rows[2], t_mlx *mlx);

/* FUNCTIONS */
int				line_start(t_v2 *m, char which, t_mlx *mlx);
void			reset_buffer(t_mlx *mlx);
int				get_pixel(t_mlx *mlx, int px, int py);
void			put_background_to_image(int *yx, char *buffer, int color,
					t_mlx *mlx);
void			put_color_to_pixel(int *yx, char *buffer, int color,
					t_mlx *mlx);
int				mouse_move(int x, int y, t_mlx *mlx);
int				key_down(int keycode, t_mlx *mlx);
int				mouse_release_hook(int keycode, int x, int y, t_mlx *mlx);
int				mouse_press_hook(int keycode, int x, int y, t_mlx *mlx);
int				get_positioning(int i, t_mlx *mlx, char *str);
float			dist_int(t_v2 player, t_v2 ray);
int				draw_minimap(t_mlx *mlx);

#endif
