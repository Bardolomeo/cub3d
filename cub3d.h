/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:55:41 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/22 20:59:26 by gsapio           ###   ########.fr       */
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
# define PLAYER_DIM 8
# define VELOCITY 10

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
}			t_f_v2;

typedef struct s_image
{
	void	*img_ptr;
	int		i_height;
	int		i_width;
}			t_image;

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

// drawing
void		DDA(t_v2 vec0, t_v2 vec1, t_mlx *mlx);
int			draw_map(t_mlx *mlx);
int			draw_player(t_mlx *mlx);
void		draw_tile(int color, int i, int j, t_mlx *mlx);
t_v2		player_pos(t_mlx *mlx);
void		find_player_in_map(char **map, int *i, int *j, t_v2 *vector);
int			enlarge_map(t_mlx *mlx);

#endif
