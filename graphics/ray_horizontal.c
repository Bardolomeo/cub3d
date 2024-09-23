/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horizontal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:49:53 by gsapio            #+#    #+#             */
/*   Updated: 2024/07/04 18:21:05 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_h_ray(t_mlx *mlx, int tile_dim)
{
	double	co_tan;

	mlx->ray_h.ray.angle = mlx->pos.angle;
	mlx->ray_h.dof = 0;
	co_tan = -1 / tan(mlx->pos.angle);
	set_ray_coordinates_h(mlx, co_tan, tile_dim);
}

void	set_ray_coordinates_h(t_mlx *mlx, float coTan, int tile_dim)
{
	if (mlx->ray_h.ray.angle > PI)
	{
		mlx->ray_h.ray.fy = ((((int)mlx->pos.y >> (int)log2(tile_dim))
					<< (int)log2(tile_dim))) - 0.1;
		mlx->ray_h.ray.fx = (mlx->pos.y - mlx->ray_h.ray.fy) * coTan
			+ mlx->pos.x;
		mlx->ray_h.off.fy = -tile_dim;
		mlx->ray_h.off.fx = -mlx->ray_h.off.fy * coTan;
	}
	if (mlx->ray_h.ray.angle < PI)
	{
		mlx->ray_h.ray.fy = ((((int)mlx->pos.y >> (int)log2(tile_dim))
					<< (int)log2(tile_dim))
				+ tile_dim);
		mlx->ray_h.ray.fx = (mlx->pos.y - mlx->ray_h.ray.fy) * coTan
			+ mlx->pos.x;
		mlx->ray_h.off.fy = tile_dim;
		mlx->ray_h.off.fx = -mlx->ray_h.off.fy * coTan;
	}
	float_comp_conditional(mlx, &mlx->ray_h);
}

int	line_start(t_v2 *m, char which, t_mlx *mlx)
{
	int	i;

	i = 0;
	if (which == 'x')
		while (mlx->map[m->y][i] && mlx->map[m->y][i] != '1')
			i++;
	if (which == 'y')
		while (mlx->map[i][m->x] && mlx->map[i][m->x] != '1')
			i++;
	return (i - 2);
}

int	cast_hrays_loop(t_mlx *mlx, t_v2 *m, int cols_rows[2])
{
	if (m->y < 0 || m->y > cols_rows[0] || m->x > cols_rows[1] || m->x < 0)
		return (re_calculate_ray(mlx, m, cols_rows));
	if ((m->y >= 0 && m->x >= 0) && (m->y <= cols_rows[0]
			&& m->x <= (int)ft_strlen(mlx->map[m->y]))
		&& mlx->map[m->y][m->x] == '1')
	{
		mlx->dist_h = dist(mlx->pos, mlx->ray_h.ray);
		return (1);
	}
	else
	{
		mlx->ray_h.ray.fx += mlx->ray_h.off.fx;
		mlx->ray_h.ray.fy += mlx->ray_h.off.fy;
		mlx->ray_h.dof += 1;
	}
	return (0);
}

int	casting_rays_horizontal(t_mlx *mlx, int tile_dim)
{
	t_v2	m;
	int		cols_rows[2];
	int		cast_res;

	m.x = 0;
	m.y = 0;
	count_cols_rows(&cols_rows[0], &cols_rows[1], mlx->map);
	set_limit_dof(cols_rows, mlx);
	set_h_ray(mlx, tile_dim);
	while (mlx->ray_h.dof < mlx->limit_dof)
	{
		m.x = (int)(mlx->ray_h.ray.fx) >> (int)log2(tile_dim);
		m.y = ((int)(mlx->ray_h.ray.fy) >> (int)log2(tile_dim));
		cast_res = cast_hrays_loop(mlx, &m, cols_rows);
		if (cast_res == 1)
			break ;
	}
	return (1);
}
