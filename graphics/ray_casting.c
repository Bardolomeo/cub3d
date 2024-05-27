/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:03:38 by bard              #+#    #+#             */
/*   Updated: 2024/05/27 21:14:15 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

int	float_comp(float first, float second)
{
    // Calculate the difference.
    float	diff;
	float	largest;
	
	diff = fabs(first - second);
    first = fabs(first);
    second = fabs(second);
    // Find the largest
	if (second > first)
		largest = second;
	else
		largest = first;
    if (diff <= largest * FLT_EPSILON)
        return (1);
    return (0);
}

void	set_ray_coordinates_h(t_mlx *mlx, float aTan, float pi_2, float pi_3)
{

	if (mlx->ray_h.ray.angle > PI)
	{
		mlx->ray_h.ray.fy = (((int)mlx->pos.y >> (int)log2(TILE_DIM)) << (int)log2(TILE_DIM)) + TILE_DIM;
		mlx->ray_h.ray.fx = (mlx->pos.y - mlx->ray_h.ray.fy)* aTan + mlx->pos.x;
		mlx->ray_h.off.fy = TILE_DIM;
		mlx->ray_h.off.fx = -mlx->ray_h.off.fy * aTan;
	}
	if (mlx->ray_h.ray.angle < PI)
	{
		mlx->ray_h.ray.fy = (((int)mlx->pos.y >> (int)log2(TILE_DIM) ) << (int)log2(TILE_DIM)) - 0.0001;
		mlx->ray_h.ray.fx = (mlx->pos.y - mlx->ray_h.ray.fy) * aTan + mlx->pos.x;
		mlx->ray_h.off.fy = -TILE_DIM;
		mlx->ray_h.off.fx = -mlx->ray_h.off.fy * aTan;
	}
	if (float_comp(mlx->ray_v.ray.angle, pi_3) || float_comp(mlx->ray_v.ray.angle, pi_2) ||
		float_comp(mlx->ray_v.ray.angle, 0) || float_comp(mlx->ray_v.ray.angle, (float)(PI)))
	{
		mlx->ray_h.ray.fx = mlx->pos.x;
		mlx->ray_h.ray.fy = mlx->pos.y;
		mlx->ray_v.off.fx = 0;
		mlx->ray_v.off.fy = 0;
		mlx->ray_h.dof = TILE_DIM / 2;
	}
}
void	set_h_ray(t_mlx *mlx)
{
	double	aTan;
	float	pi_2;
	float	pi_3;

	mlx->ray_h.ray.angle = mlx->pos.angle;
	mlx->ray_h.dof = 0;
	pi_2 = (PI / 2);
	pi_3 = PI_3;
	aTan = -1/tan(mlx->pos.angle);
	set_ray_coordinates_h(mlx, aTan, pi_2, pi_3);
}


void	set_v_ray(t_mlx *mlx)
{
	double	nTan;
	float	pi_2;
	float	pi_3;

	mlx->ray_v.ray.angle = mlx->pos.angle;
	mlx->ray_v.dof = 0;
	nTan = -(tan(mlx->ray_h.ray.angle));
	pi_2 = (PI / 2);
	pi_3 = PI_3;
	set_ray_coordinates_v(mlx, nTan, pi_2, pi_3);
}

void	set_ray_coordinates_v(t_mlx *mlx, float nTan, float pi_2, float pi_3)
{
	if (mlx->ray_v.ray.angle > pi_2 && (mlx->ray_v.ray.angle < pi_3))
	{
		mlx->ray_v.ray.fx = (((int)mlx->pos.x >> (int)log2(TILE_DIM)) << (int)log2(TILE_DIM)) + TILE_DIM;
		mlx->ray_v.ray.fy = (mlx->pos.x - mlx->ray_v.ray.fx)* nTan + mlx->pos.y;
		mlx->ray_v.off.fx = TILE_DIM;
		mlx->ray_v.off.fy = -mlx->ray_v.off.fx * nTan;
	}
	if (mlx->ray_v.ray.angle < pi_2 || mlx->ray_v.ray.angle > pi_3)
	{
		mlx->ray_v.ray.fx = (((int)mlx->pos.x >> (int)log2(TILE_DIM) ) << (int)log2(TILE_DIM)) - 0.0001;
		mlx->ray_v.ray.fy = (mlx->pos.x - mlx->ray_v.ray.fx) * nTan + mlx->pos.y;
		mlx->ray_v.off.fx = -TILE_DIM;
		mlx->ray_v.off.fy = -mlx->ray_v.off.fx * nTan;
	}
	if (float_comp(mlx->ray_v.ray.angle, pi_3) || 		float_comp(mlx->ray_v.ray.angle, pi_2) ||
		float_comp(mlx->ray_v.ray.angle, 0) || float_comp(mlx->ray_v.ray.angle, (float)(PI)))
	{
		mlx->ray_v.ray.fx = mlx->pos.x;
		mlx->ray_v.ray.fy = mlx->pos.y;
		mlx->ray_v.dof = TILE_DIM / 2;
	}
}

int	casting_rays_horizontal(t_mlx *mlx)
{
	t_v2	m;
	int		nrows;
	int		ncols;
	
	count_cols_rows(&ncols, &nrows, mlx->map);	
	set_h_ray(mlx);
	while (mlx->ray_h.dof < TILE_DIM / 2)
	{
		m.x = (int)(mlx->ray_h.ray.fx) >> (int)log2(TILE_DIM);
		m.y = (int)(mlx->ray_h.ray.fy) >> (int)log2(TILE_DIM);
		if (m.x < 0 || m.x > nrows)
			m.x = 0;
		if (m.y < 0 || m.y > ncols)
			m.y = 0;
		if ((m.y >= 0 && m.x >= 0) && (m.y <= ncols && m.x <= nrows) && mlx->map[m.y][m.x] == '1')
		{
			mlx->dist_h = dist(mlx->pos, mlx->ray_h.ray);
			mlx->ray_h.dof = TILE_DIM / 2;
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

	count_cols_rows(&ncols, &nrows, mlx->map);	
	set_v_ray(mlx);
	while (mlx->ray_v.dof < TILE_DIM / 2)
	{
		m.x = (int)mlx->ray_v.ray.fx >> (int)log2(TILE_DIM);
		m.y = (int)mlx->ray_v.ray.fy >> (int)log2(TILE_DIM);
		if (m.x < 0 || m.x > nrows)
			m.x = 0;
		if (m.y < 0 || m.y > ncols)
			m.y = 0;
		if ((m.y >= 0 && m.x >= 0) && ((m.y <= ncols && m.x <= nrows) && mlx->map[m.y][m.x] == '1'))
		{	
			mlx->ray_v.dof = TILE_DIM / 2;
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
	double	degree;
	static int	count = -1;
	static double dgr_range = DGR;

	degree = DGR;
	if (++count < 15)
		mlx->pos.angle -= dgr_range;
	if (count >= 15 && count < 30)
		mlx->pos.angle += dgr_range;
	casting_rays_horizontal(mlx);
	casting_rays_vertical(mlx);
	if (count < 15)
		mlx->pos.angle += dgr_range;
	if (count == 30)
	{
		count = -1;
	}
	if (count == 14 || count == -1)
		dgr_range = DGR;
	if (count >= 15)
		mlx->pos.angle -= dgr_range;
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
	dgr_range += degree;
	return (1);
}
