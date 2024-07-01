/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horizontal_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:41:38 by gsapio            #+#    #+#             */
/*   Updated: 2024/07/01 21:01:14 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int re_calculate_ray(t_mlx *mlx, t_v2 *m, t_f_v2 src_ray, int cols_rows[2])
{
	if (abs((int)mlx->ray_h.off.fx) >= 3 && abs((int)mlx->ray_h.off.fy) >= 3)
	{
		mlx->ray_h.dof = 0;
		mlx->ray_h.off.fx /= 1.2;
		mlx->ray_h.off.fy /= 1.2;
		mlx->ray_h.ray = src_ray;
		return (0);
	}
	else 
	{
		if (m->y < 0 || m->y > cols_rows[0])
			m->y = 0;
		if (m->x < 0 || m->x > cols_rows[1])
			m->x = 0;
		mlx->dist_h = 1921;
		return (1);
	}
}

void    set_limit_dof(int cols_rows[2], t_mlx *mlx)
{
	if (cols_rows[0] > cols_rows[1])
		mlx->limit_dof = cols_rows[0];
	else
		mlx->limit_dof = cols_rows[1];
}

int	ray_vertical_recalculate(t_v2 *m, int cols_rows[2], t_f_v2 src_ray, t_mlx *mlx)
{
	if (m->y < 0 || m->y > cols_rows[0] || m->x > (int)ft_strlen(mlx->map[m->y]) 
		|| m->x < 0)
	{
		if (abs((int)mlx->ray_v.off.fx) >= 3 && abs((int)mlx->ray_v.off.fy >= 3))
		{
			mlx->ray_v.dof = 0;
			mlx->ray_v.off.fx /= 1.2;
			mlx->ray_v.off.fy /= 1.2;
			mlx->ray_v.ray = src_ray;
			return (0);
		}
		else 
		{
			if (m->y < 0 || m->y > cols_rows[0])
				m->y = 0;
			if (m->x < 0 || m->x > cols_rows[1])
				m->x = 0;
			mlx->dist_v = mlx->dist_h + 1;
			return (1);
		}
	}
	if (raycast_vertical_loop(mlx, *m, cols_rows[1], cols_rows[0]))
		return (1);
	return (0);
}