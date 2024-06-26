/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:50:28 by mtani             #+#    #+#             */
/*   Updated: 2024/06/26 17:52:10 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	wall_index(t_mlx *mlx)
{
	if (mlx->dist_t == mlx->dist_v)
	{
		if (mlx->int_ray.angle > PI / 2 && mlx->int_ray.angle < 3 * (PI / 2))
			return (WE);
		else
			return (EA);
	}
	else
	{
		if (mlx->int_ray.angle > 0 && mlx->int_ray.angle < PI)
			return (SO);
		else
			return (NO);
	}
	return (0);
}

void	make_wall_in_image(t_mlx *mlx, int x, int y, t_texture tex)
{
	int		ind[2];
	char	*buffer[2];
	int		yx[2];

	buffer[0] = mlx_get_data_addr(mlx->ceil_floor.img_ptr,
			&mlx->ceil_floor.pixel_bits, &mlx->ceil_floor.line_bytes,
			&mlx->ceil_floor.endian);
	buffer[1] = mlx_get_data_addr(mlx->images[wall_index(mlx)].img_ptr,
			&mlx->images[wall_index(mlx)].pixel_bits,
			&mlx->images[wall_index(mlx)].line_bytes,
			&mlx->images[wall_index(mlx)].endian);
	ind[0] = (y * mlx->ceil_floor.line_bytes) + (x * 4);
	ind[1] = ((int)(tex.ty) *(mlx->images[NO].i_height) + (int)(tex.tx)) * 4;
	if (buffer[1])
	{
		yx[0] = y;
		yx[1] = x;
		put_color_to_wall(mlx, yx, buffer, ind);
	}
}

void	check_distance(t_mlx *mlx)
{
	if (mlx->dist_h > mlx->dist_v)
	{
		mlx->int_ray.x = mlx->ray_v.ray.fx;
		mlx->int_ray.y = mlx->ray_v.ray.fy;
		mlx->int_ray.angle = mlx->ray_v.ray.angle;
		mlx->dist_t = mlx->dist_v;
	}
	else
	{
		mlx->int_ray.x = mlx->ray_h.ray.fx;
		mlx->int_ray.y = mlx->ray_h.ray.fy;
		mlx->int_ray.angle = mlx->ray_h.ray.angle;
		mlx->dist_t = mlx->dist_h;
	}
}

void	map_pos(t_mlx *mlx, int mode)
{
	if (mode == 1)
	{
		mlx->pos_handle = mlx->pos;
		mlx->pos.x /= 8;
		mlx->pos.y /= 8;
	}
	if (mode == 0)
		mlx->pos = mlx->pos_handle;
}

int	draw_minimap(t_mlx *mlx)
{
	int	count;

	map_pos(mlx, 1);
	mlx->pos.angle -= DGR * 30;
	if (mlx->pos.angle >= 2 * PI)
		mlx->pos.angle -= 2 * PI;
	count = -1;
	while (++count < VIEWPORT_W)
	{
		casting_rays(&count, mlx, MAP_TILE_DIM);
		check_distance(mlx);
		dda(mlx->pos, mlx->int_ray, 0x00ffff, mlx);
	}
	mlx->pos.angle += DGR * 30;
	draw_map(mlx);
	draw_player_iterative(mlx);
	map_pos(mlx, 0);
	return (1);
}
