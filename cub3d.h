/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bard <bard@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:55:41 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/23 15:49:13 by bard             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx-linux/mlx.h"
# include "Libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define TILE_DIM 32
# define PLAYER_DIM 4
# define VELOCITY 10
# define RADIAN
# define PI 3.14159265359

typedef struct s_v2
{
	int		x;
	int		y;
	float	angle;
}			t_v2;

typedef struct s_f_v2
{
	float	fx;
	float	fy;
	float	angle;
}			t_f_v2;

typedef struct s_image
{
	void	*img_ptr;
	int		i_height;
	int		i_width;
}			t_image;

typedef	struct	s_ray_vars
{
	int		dof; 
	t_f_v2	ray;
	t_f_v2	off;
}	t_ray_vars;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	char	**fmap;
	char	**map;
	t_image	images[4];
	int		floor_color;
	int		ceiling_color;
	t_v2	pos;
	t_v2	dir;
	t_ray_vars ray_v;
}			t_mlx;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}			t_rgb;

int			parse_file(int argc, char **argv, t_mlx *mlx);

// bit_colors
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);

// Utils
int			destroy_game(t_mlx *mlx);
int			destroy_game_on_start(t_mlx *mlx);
int			error_fclose(int *fd);
void		count_cols_rows(int *i, int *j, char **map);

/* Parsing */
int			check_all_elements(t_mlx *mlx);
void		set_color(char *str, int *color);
void		set_image(char *str, t_image *image, t_mlx *mlx);
int			get_elements(char *str, t_mlx *mlx);
int			check_elements(int fd, char **argv, t_mlx *mlx);
int			skip_spaces(char *str);
int			valid_chars(char tile);
int			valid_tile(char **map, int i, int j);
int			valid_player(char tile);
int			map_manager(int fd, char **argv, t_mlx *mlx);

// graphics
void		DDA(t_v2 vec0, t_v2 vec1, t_mlx *mlx);
int			draw_map(t_mlx *mlx);
int			draw_player_loop(t_mlx *mlx);
int			draw_player_iterative(t_mlx *mlx);
void		draw_tile(int color, int i, int j, t_mlx *mlx);
t_v2		player_pos(t_mlx *mlx);
void		find_player_in_map(char **map, int *i, int *j, t_v2 *vector);
int			casting_rays(t_mlx *mlx);



//movement
void		on_move(t_mlx *mlx, int keycode, float pdy, float pdx);
void		on_rotate(t_mlx *mlx, int keycode);
void		compute_direction(t_mlx *mlx, float *pdx, float *pdy);

#endif
