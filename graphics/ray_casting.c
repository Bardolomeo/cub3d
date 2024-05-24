/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bard <bard@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:03:38 by bard              #+#    #+#             */
/*   Updated: 2024/05/23 16:07:15 by bard             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <X11/Xlib.h>
#include <math.h>

void	set_ray_coordinates(t_mlx *mlx)
{
	float_t	aTan;

	mlx->ray_v.ray.angle = mlx->pos.angle;
	mlx->ray_v.dof = 0;
	aTan = -1 / tan(mlx->ray_v.ray.angle);
	if (mlx->ray_v.ray.angle == (float)(PI / 2) || mlx->ray_v.ray.angle == (float)(PI / 4 * 3))
		aTan = 0;
	if (mlx->ray_v.ray.angle < PI)
	{
		mlx->ray_v.ray.fy = (((int)mlx->pos.y >> 6) << 6) + 64;
		mlx->ray_v.ray.fx = (mlx->pos.y - mlx->ray_v.ray.fy) * (aTan + mlx->pos.x);
		mlx->ray_v.off.fy = 64;
		mlx->ray_v.off.fx = -(mlx->ray_v.off.fy) * aTan;
	}
	if (mlx->ray_v.ray.angle > PI)
	{
		mlx->ray_v.ray.fy = (((int)mlx->pos.y >> 6 ) << 6) - 0.0001;
		mlx->ray_v.ray.fx = (mlx->pos.y - mlx->ray_v.ray.fy) * (aTan + mlx->pos.x);
		mlx->ray_v.off.fy = -64;
		mlx->ray_v.off.fx = -(mlx->ray_v.off.fy) * aTan;
	}
	if (mlx->ray_v.ray.angle == 0 || mlx->ray_v.ray.angle == (float)(PI))
	{
		mlx->ray_v.ray.fx = mlx->pos.x;
		mlx->ray_v.ray.fy = mlx->pos.y;
		mlx->ray_v.dof = 8;
	}
}

int	casting_rays(t_mlx *mlx)
{
	t_v2	m;
	int		nrows;
	int		ncols;

	nrows = 0;
	ncols = 0;
	set_ray_coordinates(mlx);
	count_cols_rows(&ncols, &nrows, mlx->map);	
	while (mlx->ray_v.dof < 8)
	{
		m.x = (int)mlx->ray_v.ray.fx >> 6;
		m.y = (int)mlx->ray_v.ray.fy >> 6;
		if (((m.y > -1 && m.y < ncols) && (m.x >= 0 && m.x < nrows))  && mlx->map[m.y][m.x] == '1')
		{
			mlx->ray_v.dof = 8;
			printf("looking at a wall");
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