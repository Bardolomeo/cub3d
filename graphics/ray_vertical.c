/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vertical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:52:17 by gsapio            #+#    #+#             */
/*   Updated: 2024/07/04 20:08:18 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_v_ray(t_mlx *mlx, int tile_dim)
{
	double	n_tan;
	float	pi_2;

	mlx->ray_v.ray.angle = mlx->pos.angle;
	mlx->ray_v.dof = 0;
	n_tan = -(sin(mlx->ray_v.ray.angle) / cos(mlx->ray_v.ray.angle));
	pi_2 = (PI / 2);
	set_ray_coordinates_v(mlx, n_tan, pi_2, tile_dim);
}

int	float_comp_conditional(t_mlx *mlx, t_ray_vars *ray)
{
	if (float_comp(ray->ray.angle, PI_3) || float_comp(ray->ray.angle, PI_2)
		|| float_comp(ray->ray.angle, 0) || float_comp(ray->ray.angle,
			(float)(PI)))
	{
		ray->ray.fx = mlx->pos.x;
		ray->ray.fy = mlx->pos.y;
		return (1);
	}
	return (0);
}

void	set_ray_coordinates_v(t_mlx *mlx, float nTan, float pi_2, int tile_dim)
{
	if (mlx->ray_v.ray.angle < pi_2 || (mlx->ray_v.ray.angle > PI_3))
	{
		mlx->ray_v.ray.fx = (((int)mlx->pos.x >> (int)log2(tile_dim))
				<< (int)log2(tile_dim)) + tile_dim;
		mlx->ray_v.ray.fy = (mlx->pos.x - mlx->ray_v.ray.fx) * nTan
			+ mlx->pos.y;
		mlx->ray_v.off.fx = tile_dim;
		mlx->ray_v.off.fy = -mlx->ray_v.off.fx * nTan;
	}
	if (mlx->ray_v.ray.angle > pi_2 && mlx->ray_v.ray.angle < PI_3)
	{
		mlx->ray_v.ray.fx = (((int)mlx->pos.x >> (int)log2(tile_dim))
				<< (int)log2(tile_dim)) - 0.1;
		mlx->ray_v.ray.fy = (mlx->pos.x - mlx->ray_v.ray.fx) * nTan
			+ mlx->pos.y;
		mlx->ray_v.off.fx = -tile_dim;
		mlx->ray_v.off.fy = -mlx->ray_v.off.fx * nTan;
	}
	float_comp_conditional(mlx, &mlx->ray_v);
}

int	raycast_vertical_loop(t_mlx *mlx, t_v2 m, int nrows, int ncols)
{
	if ((m.y >= 0 && m.x >= 0) && ((m.y <= ncols && m.x <= nrows)
			&& mlx->map[m.y][m.x] == '1'))
	{
		mlx->dist_v = dist(mlx->pos, mlx->ray_v.ray);
		return (1);
	}
	else
	{
		mlx->ray_v.ray.fx += mlx->ray_v.off.fx;
		mlx->ray_v.ray.fy += mlx->ray_v.off.fy;
		mlx->ray_v.dof += 1;
		return (0);
	}
}

int	casting_rays_vertical(t_mlx *mlx, int tile_dim)
{
	t_v2	m;
	int		cols_rows[2];
	int		tmp;

	m.x = 0;
	m.y = 0;
	count_cols_rows(&cols_rows[0], &cols_rows[1], mlx->map);
	set_v_ray(mlx, tile_dim);
	while (mlx->ray_v.dof < mlx->limit_dof)
	{
		m.x = (int)mlx->ray_v.ray.fx >> (int)log2(tile_dim);
		m.y = (int)mlx->ray_v.ray.fy >> (int)log2(tile_dim);
		tmp = ray_vertical_recalculate(&m, cols_rows, mlx);
		if (tmp == 1)
			break ;
	}
	return (1);
}
