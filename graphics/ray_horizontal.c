/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horizontal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bard <bard@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:49:53 by gsapio            #+#    #+#             */
/*   Updated: 2024/06/04 07:56:13 by bard             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_h_ray(t_mlx *mlx, int tile_dim)
{
	double	coTan;

	mlx->ray_h.ray.angle = mlx->pos.angle;
	mlx->ray_h.dof = 0;
	coTan = -1/tan(mlx->pos.angle);
	set_ray_coordinates_h(mlx, coTan, tile_dim);
}

void	set_ray_coordinates_h(t_mlx *mlx, float coTan, int tile_dim)
{

	if (mlx->ray_h.ray.angle > PI)
	{
		mlx->ray_h.ray.fy = ((((int)mlx->pos.y >> (int)log2(tile_dim) ) << (int)log2(tile_dim))) - 0.0001;
		mlx->ray_h.ray.fx = (mlx->pos.y - mlx->ray_h.ray.fy) * coTan + mlx->pos.x;
		mlx->ray_h.off.fy = -tile_dim;
		mlx->ray_h.off.fx = -mlx->ray_h.off.fy * coTan;
	}
	if (mlx->ray_h.ray.angle < PI)
	{
		mlx->ray_h.ray.fy = ((((int)mlx->pos.y >> (int)log2(tile_dim)) << (int)log2(tile_dim)) + tile_dim);
		mlx->ray_h.ray.fx = (mlx->pos.y - mlx->ray_h.ray.fy)* coTan + mlx->pos.x;
		mlx->ray_h.off.fy = tile_dim;
		mlx->ray_h.off.fx = -mlx->ray_h.off.fy * coTan;
	}
	if (float_comp(mlx->pos.angle, PI) || float_comp(mlx->pos.angle, 0))
	{
		mlx->ray_h.ray.fx = mlx->pos.x;
		mlx->ray_h.ray.fy = mlx->pos.y;
		mlx->ray_h.dof = mlx->limit_dof;
	}
}

int	casting_rays_horizontal(t_mlx *mlx, int tile_dim)
{
	t_v2	m;
	int		nrows;
	int		ncols;
	
	count_cols_rows(&ncols, &nrows, mlx->map);	
	if (ncols > nrows)
		mlx->limit_dof = ncols;
	else
		mlx->limit_dof = nrows;
	set_h_ray(mlx, tile_dim);
	while (mlx->ray_h.dof < mlx->limit_dof)
	{
		m.x = (int)(mlx->ray_h.ray.fx) >> (int)log2(tile_dim);
		m.y = ((int)(mlx->ray_h.ray.fy) >> (int)log2(tile_dim));
		if (m.x < 0 || m.x > nrows)
			m.x = 0;
		if (m.y < 0 || m.y > ncols)
			m.y = 0;
		if ((m.y >= 0 && m.x >= 0) && (m.y <= ncols && m.x <= nrows) && mlx->map[m.y][m.x] == '1')
		{
			mlx->dist_h = dist(mlx->pos, mlx->ray_h.ray);
			break ;
		}
		else
		{
			mlx->ray_h.ray.fx += mlx->ray_h.off.fx;
			mlx->ray_h.ray.fy += mlx->ray_h.off.fy;
			mlx->ray_h.dof += 1;
		}
	}
	if (mlx->ray_h.dof == mlx->limit_dof)
		mlx->dist_h = mlx->prev_dist_h;
	mlx->prev_dist_h = mlx->dist_h;
	return (1);
}
