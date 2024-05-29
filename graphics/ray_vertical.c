/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vertical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:52:17 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/29 16:51:33 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_v_ray(t_mlx *mlx)
{
	double	nTan;
	float	pi_2;
	float	pi_3;

	mlx->ray_v.ray.angle = mlx->pos.angle;
	mlx->ray_v.dof = 0;
	nTan = -(((sin(mlx->ray_v.ray.angle)) / cos(mlx->ray_v.ray.angle)));
	pi_2 = (PI / 2);
	pi_3 = PI_3;
	set_ray_coordinates_v(mlx, nTan, pi_2, pi_3);
}

void	set_ray_coordinates_v(t_mlx *mlx, float nTan, float pi_2, float pi_3)
{
	if (mlx->ray_v.ray.angle < pi_2 || (mlx->ray_v.ray.angle > pi_3))
	{
		mlx->ray_v.ray.fx = (((int)mlx->pos.x >> 3) << 3) + TILE_DIM;
		mlx->ray_v.ray.fy = (mlx->pos.x - mlx->ray_v.ray.fx)* nTan + mlx->pos.y;
		mlx->ray_v.off.fx = TILE_DIM;
		mlx->ray_v.off.fy = -mlx->ray_v.off.fx * nTan;
	}
	if (mlx->ray_v.ray.angle > pi_2 && mlx->ray_v.ray.angle < pi_3)
	{
		mlx->ray_v.ray.fx = (((int)mlx->pos.x >> 3 ) << 3) - 0.0001;
		mlx->ray_v.ray.fy = (mlx->pos.x - mlx->ray_v.ray.fx) * nTan + mlx->pos.y;
		mlx->ray_v.off.fx = -TILE_DIM;
		mlx->ray_v.off.fy = -mlx->ray_v.off.fx * nTan;
	}
	if (float_comp(mlx->ray_v.ray.angle, pi_3) || float_comp(mlx->ray_v.ray.angle, pi_2) || float_comp(mlx->ray_v.ray.angle, 0) || float_comp(mlx->ray_v.ray.angle, (float)(PI)))
	{
		mlx->ray_v.ray.fx = mlx->pos.x;
		mlx->ray_v.ray.fy = mlx->pos.y;
		mlx->ray_v.dof = mlx->limit_dof;
	}
}

int	casting_rays_vertical(t_mlx *mlx)
{
	t_v2	m;
	int		nrows;
	int		ncols;

	count_cols_rows(&ncols, &nrows, mlx->map);	
	set_v_ray(mlx);
	while (mlx->ray_v.dof < mlx->limit_dof)
	{
		m.x = (int)mlx->ray_v.ray.fx >> 3; /*(int)log2(TILE_DIM)*/
		m.y = (int)mlx->ray_v.ray.fy >> 3;
		if (m.x < 0 || m.x > nrows)
			m.x = 0;
		if (m.y < 0 || m.y > ncols)
			m.y = 0;
		if ((m.y >= 0 && m.x >= 0) && ((m.y <= ncols && m.x <= nrows) && mlx->map[m.y][m.x] == '1'))
		{	
			mlx->dist_v = dist(mlx->pos, mlx->ray_v.ray);
			break ;
		}
		else
		{
			mlx->ray_v.ray.fx += mlx->ray_v.off.fx;
			mlx->ray_v.ray.fy += mlx->ray_v.off.fy;
			mlx->ray_v.dof += 1;
		}
	}
	if (mlx->ray_v.dof == mlx->limit_dof)
		mlx->dist_v = mlx->prev_dist_v;
	mlx->prev_dist_v = mlx->dist_v;
	return (1);
}
