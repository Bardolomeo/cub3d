/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horizontal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:49:53 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/28 18:29:09 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_h_ray(t_mlx *mlx)
{
	double	coTan;

	mlx->ray_h.ray.angle = mlx->pos.angle;
	mlx->ray_h.dof = 0;
	coTan = -1/tan(mlx->pos.angle);
	set_ray_coordinates_h(mlx, coTan);
}

void	set_ray_coordinates_h(t_mlx *mlx, float coTan)
{

	if (mlx->ray_h.ray.angle > PI)
	{
		mlx->ray_h.ray.fy = ((((int)mlx->pos.y >> (int)log2(TILE_DIM) ) << (int)log2(TILE_DIM)) - 0.0001);
		mlx->ray_h.ray.fx = (mlx->pos.y - mlx->ray_h.ray.fy) * coTan + mlx->pos.x;
		mlx->ray_h.off.fy = -TILE_DIM;
		mlx->ray_h.off.fx = -mlx->ray_h.off.fy * coTan;
	}
	if (mlx->ray_h.ray.angle < PI)
	{
		mlx->ray_h.ray.fy = ((((int)mlx->pos.y >> (int)log2(TILE_DIM)) << (int)log2(TILE_DIM)) + TILE_DIM);
		mlx->ray_h.ray.fx = (mlx->pos.y - mlx->ray_h.ray.fy)* coTan + mlx->pos.x;
		mlx->ray_h.off.fy = TILE_DIM;
		mlx->ray_h.off.fx = -mlx->ray_h.off.fy * coTan;
	}
	if (float_comp(mlx->pos.angle, 0) || float_comp(mlx->pos.angle, 0))
	{
		mlx->ray_v.ray.fx = mlx->pos.x;
		mlx->ray_v.ray.fy = mlx->pos.y;
		mlx->ray_v.dof = TILE_DIM / 4;
	}
}

int	casting_rays_horizontal(t_mlx *mlx)
{
	t_v2	m;
	int		nrows;
	int		ncols;
	
	count_cols_rows(&ncols, &nrows, mlx->map);	
	set_h_ray(mlx);
	while (mlx->ray_h.dof < TILE_DIM / 4)
	{
		m.x = (int)(mlx->ray_h.ray.fx) >> (int)log2(TILE_DIM);
		m.y = ((int)(mlx->ray_h.ray.fy) >> (int)log2(TILE_DIM));
		if (m.x < 0 || m.x > nrows)
			m.x = 0;
		if (m.y < 0 || m.y > ncols)
			m.y = 0;
		if ((m.y >= 0 && m.x >= 0) && (m.y <= ncols && m.x <= nrows) && mlx->map[m.y][m.x] == '1')
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
