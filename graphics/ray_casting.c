/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:03:38 by bard              #+#    #+#             */
/*   Updated: 2024/05/28 18:57:15 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

void	draw_ceiling_floor(t_mlx *mlx)
{
	int	i;
	int	j;

	i =  640;
	while (++i < 1920)
	{
		j = 0;
		while (j < 540)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, i, j, mlx->ceiling_color);
			j++;
		}
		while (j >= 540 && j < 1081)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, i, j, mlx->floor_color);
			j++;
		}
	}
}

void	draw_lines(t_mlx *mlx, int count)
{
	int	i;
	int	j;
	int con;
	t_v2	pos_vec;
	t_v2	line;

	con = 0;
	count_cols_rows(&i, &j, mlx->map);
	line.y = (i * j) * 320 / mlx->dist_t;
	if (line.y > 1020)
		line.y = 1020;
}

void	casting_rays(int *count, t_mlx *mlx, double *dgr_range)
{	
	if (++(*count) < 15)
		mlx->pos.angle -= (*dgr_range);
	if ((*count) >= 15 && (*count) < 30)
		mlx->pos.angle += (*dgr_range);
	casting_rays_horizontal(mlx);
	casting_rays_vertical(mlx);
	if (*count < 15)
		mlx->pos.angle += (*dgr_range);
	if (*count == 30)
	{
		*count = -1;
	}
	if (*count == 14 || *count == -1)
		*dgr_range = DGR;
	if (*count >= 15)
		mlx->pos.angle -= *dgr_range;
}

int	draw_walls(t_mlx *mlx)
{
	t_v2	int_ray;
	double	degree;
	static int	count = -1;
	static double dgr_range = DGR;

	degree = DGR;
	casting_rays(&count, mlx, &dgr_range);
	draw_ceiling_floor(mlx);
	if (mlx->dist_h > mlx->dist_v)
	{
		int_ray.x = mlx->ray_v.ray.fx;
		int_ray.y = mlx->ray_v.ray.fy;
		mlx->dist_t = mlx->dist_v;
	}
	else
	{
		int_ray.x = mlx->ray_h.ray.fx;
		int_ray.y = mlx->ray_h.ray.fy;
		mlx->dist_t = mlx->dist_h;
	}
	draw_lines(mlx, count);
	DDA(int_ray, int_ray, 0xff0000, mlx);
	dgr_range += degree;
	return (1);
}
