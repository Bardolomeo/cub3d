/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:03:38 by bard              #+#    #+#             */
/*   Updated: 2024/05/24 19:09:35 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>


void	set_ray_coordinates_h(t_mlx *mlx)
{
	double	aTan;
	double	one_deg;
	static double	deg_off = 0.0174533;
	static double	deg = 0.0174533;

	mlx->ray_h.ray.angle = mlx->pos.angle + deg;
	mlx->ray_h.dof = 0;
	aTan = -1 / tan(mlx->ray_h.ray.angle);
	if (mlx->ray_h.ray.angle > PI)
	{
		mlx->ray_h.ray.fy = (((int)mlx->pos.y >> (int)log2(TILE_DIM)) << (int)log2(TILE_DIM)) + TILE_DIM;
		mlx->ray_h.ray.fx = (mlx->pos.y - mlx->ray_h.ray.fy)* aTan + mlx->pos.x;
		mlx->ray_h.off.fy = TILE_DIM;
		mlx->ray_h.off.fx = -(mlx->ray_h.off.fy) * aTan;
	}
	if (mlx->ray_h.ray.angle < PI)
	{
		mlx->ray_h.ray.fy = (((int)mlx->pos.y >> (int)log2(TILE_DIM) ) << (int)log2(TILE_DIM)) - 0.0001;
		mlx->ray_h.ray.fx = (mlx->pos.y - mlx->ray_h.ray.fy) * aTan + mlx->pos.x;
		mlx->ray_h.off.fy = -TILE_DIM;
		mlx->ray_h.off.fx = -(mlx->ray_h.off.fy) * aTan;
	}
	if (mlx->ray_h.ray.angle == 0 || mlx->ray_h.ray.angle == (float)(PI))
	{
		mlx->ray_h.ray.fx = mlx->pos.x;
		mlx->ray_h.ray.fy = mlx->pos.y;
		mlx->ray_h.dof = 8;
	}
	deg += 0.02;
	if (deg == (double)(0.06))
		deg = -0.06;
}

void	set_ray_coordinates_v(t_mlx *mlx)
{
	double	nTan;
	float	pi_2;
	float	pi_3;
	static float	deg = -3 * DGR;

	mlx->ray_v.ray.angle = mlx->pos.angle + deg;
	mlx->ray_v.dof = 0;
	nTan = -(tan(mlx->ray_v.ray.angle));
	pi_2 = (PI / 2);
	pi_3 = PI_3;
	if (mlx->ray_v.ray.angle > pi_2 && (mlx->ray_v.ray.angle < pi_3))
	{
		mlx->ray_v.ray.fx = (((int)mlx->pos.x >> (int)log2(TILE_DIM)) << (int)log2(TILE_DIM)) + TILE_DIM;
		mlx->ray_v.ray.fy = (mlx->pos.x - mlx->ray_v.ray.fx)* nTan + mlx->pos.y;
		mlx->ray_v.off.fx = TILE_DIM;
		mlx->ray_v.off.fy = -(mlx->ray_v.off.fx) * nTan;
	}
	if (mlx->ray_v.ray.angle < pi_2 || mlx->ray_v.ray.angle > pi_3)
	{
		mlx->ray_v.ray.fx = (((int)mlx->pos.x >> (int)log2(TILE_DIM) ) << (int)log2(TILE_DIM)) - 0.0001;
		mlx->ray_v.ray.fy = (mlx->pos.x - mlx->ray_v.ray.fx) * nTan + mlx->pos.y;
		mlx->ray_v.off.fx = -TILE_DIM;
		mlx->ray_v.off.fy = -(mlx->ray_v.off.fx) * nTan;
	}
	if (mlx->ray_v.ray.angle == 0 || mlx->ray_v.ray.angle == (float)(PI))
	{
		mlx->ray_v.ray.fx = mlx->pos.x;
		mlx->ray_v.ray.fy = mlx->pos.y;
		mlx->ray_v.dof = 8;
	}
	deg += DGR;
	if (deg == 3 * DGR)
		deg = -3 * DGR;
}

int	casting_rays_horizontal(t_mlx *mlx)
{
	t_v2	m;
	int		nrows;
	int		ncols;
	
	set_ray_coordinates_h(mlx);
	count_cols_rows(&ncols, &nrows, mlx->map);	
	while (mlx->ray_h.dof < TILE_DIM / 4)
	{
		m.x = (int)mlx->ray_h.ray.fx >> (int)log2(TILE_DIM);
		m.y = (int)mlx->ray_h.ray.fy >> (int)log2(TILE_DIM);
		if ((m.y > 0 && m.x > 0) && (m.y < ncols && m.x < nrows) && mlx->map[m.y][m.x] == '1')
		{
			mlx->dist_h = dist(mlx->pos, mlx->ray_h.ray);
			mlx->ray_h.dof = TILE_DIM / 4;
		}
		else
		{
			mlx->ray_h.ray.fx += mlx->ray_h.off.fx;
			mlx->ray_h.ray.fy += mlx->ray_h.off.fy;
			mlx->ray_h.dof += 1;
		}
	}
	return (1);
}

int	casting_rays_vertical(t_mlx *mlx)
{
	t_v2	m;
	int		nrows;
	int		ncols;

	set_ray_coordinates_v(mlx);
	count_cols_rows(&ncols, &nrows, mlx->map);	
	while (mlx->ray_v.dof < TILE_DIM / 4)
	{
		m.x = (int)mlx->ray_v.ray.fx >> (int)log2(TILE_DIM);
		m.y = (int)mlx->ray_v.ray.fy >> (int)log2(TILE_DIM);
		if ((m.y > 0 && m.x > 0) && ((m.y < ncols && m.x < nrows) && mlx->map[m.y][m.x] == '1'))
		{	
			mlx->ray_v.dof = TILE_DIM / 4;
			mlx->dist_v = dist(mlx->pos, mlx->ray_v.ray);
		}
		else
		{
			mlx->ray_v.ray.fx += mlx->ray_v.off.fx;
			mlx->ray_v.ray.fy += mlx->ray_v.off.fy;
			mlx->ray_v.dof += 1;
		}
	}
	return (1);
}

int	casting_rays(t_mlx *mlx)
{
	t_v2	int_ray;

	casting_rays_horizontal(mlx);
	casting_rays_vertical(mlx);
	if (mlx->dist_h > mlx->dist_v)
	{
		int_ray.x = mlx->ray_v.ray.fx;
		int_ray.y = mlx->ray_v.ray.fy;
	}
	else
	{
		int_ray.x = mlx->ray_h.ray.fx;
		int_ray.y = mlx->ray_h.ray.fy;
	}
	DDA(mlx->pos, int_ray, 0xff0000, mlx);
	return (1);
}
