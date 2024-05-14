/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:55:41 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/14 17:20:13 by gsapio           ###   ########.fr       */
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
	char	**map;
	t_image	images[4];
	int		floor_color;
	int		ceiling_color;
}			t_mlx;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}			t_rgb;

int			parse_elements(int argc, char **argv, t_mlx *mlx);

// bit_colors
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);

#endif
