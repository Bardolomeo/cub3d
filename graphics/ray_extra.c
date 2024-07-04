/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:41:38 by gsapio            #+#    #+#             */
/*   Updated: 2024/07/04 18:17:20 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	re_calculate_ray(t_mlx *mlx, t_v2 *m, int cols_rows[2])
{
	if (m->y < 0 || m->y > cols_rows[0])
		m->y = 0;
	if (m->x < 0 || m->x > cols_rows[1])
		m->x = 0;
	mlx->dist_h = 1921;
	return (1);
}

void	set_limit_dof(int cols_rows[2], t_mlx *mlx)
{
	if (cols_rows[0] > cols_rows[1])
	{
		mlx->limit_dof = cols_rows[0];
	}
	else
	{
		mlx->limit_dof = cols_rows[1];
	}
	if (mlx->limit_dof > MAX_DOF)
	{
		mlx->limit_dof = MAX_DOF;
	}
}

int	ray_vertical_recalculate(t_v2 *m, int cols_rows[2], t_mlx *mlx)
{
	if (m->y < 0 || m->y > cols_rows[0] || m->x > (int)ft_strlen(mlx->map[m->y])
		|| m->x < 0)
	{
		if (m->y < 0 || m->y > cols_rows[0])
			m->y = 0;
		if (m->x < 0 || m->x > cols_rows[1])
			m->x = 0;
		mlx->dist_v = mlx->dist_h + 1;
		return (1);
	}
	if (raycast_vertical_loop(mlx, *m, cols_rows[1], cols_rows[0]))
		return (1);
	return (0);
}
