/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:03:38 by bard              #+#    #+#             */
/*   Updated: 2024/06/24 20:44:32 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

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
	ind[1] = ((int)(tex.ty) * (mlx->images[NO].i_height) + (int)(tex.tx)) * 4;
	if (buffer[1])
	{
		yx[0] = y;
		yx[1] = x;
		if (mlx->dist_t == mlx->dist_v)
			put_color_to_pixel(yx, buffer[0],
				((((buffer[1][ind[1]] & 0xFF) | (buffer[1][ind[1]
								+ 1] & 0xFF) << 8 | (buffer[1][ind[1]
								+ 2] & 0xFF) << 16) >> 1) & 0x7F7F7F), mlx);
		else
			put_color_to_pixel(yx, buffer[0],
				((buffer[1][ind[1]] & 0xFF) | (buffer[1][ind[1]
						+ 1] & 0xFF) << 8 | (buffer[1][ind[1]
						+ 2] & 0xFF) << 16), mlx);
	}
}

void	draw_single_wall(t_mlx *mlx, float line_h, float line_o, int count)
{
	int			i;
	int			j;
	t_texture	tex;

	i = -1;
	j = -1;
	tex.ty_off = 0;
	tex.ty_step = mlx->images[wall_index(mlx)].i_height / line_h;
	if (line_h > VIEWPORT_H)
	{
		tex.ty_off = (line_h - VIEWPORT_H) / 2;
		line_h = VIEWPORT_H;
	}
	line_o = (VIEWPORT_H / 2.0) - line_h / 2;
	tex.ty = tex.ty_step * tex.ty_off;
	if (mlx->dist_v < mlx->dist_h)
		tex.tx = (int)(mlx->int_ray.y) % mlx->images[wall_index(mlx)].i_width;
	else
		tex.tx = (int)(mlx->int_ray.x) % mlx->images[wall_index(mlx)].i_width;
	i = line_o;
	while (++i < line_o + line_h)
	{
		j = -1;
		while (++j < 2)
		{
			make_wall_in_image(mlx, (j + count), i, tex);
		}
		tex.ty += tex.ty_step;
	}
}

void	draw_lines(t_mlx *mlx, int count)
{
	int		i;
	int		j;
	float	line_o;
	float	line_h;

	count_cols_rows(&i, &j, mlx->map);
	line_h = (mlx->images[wall_index(mlx)].i_height) * VIEWPORT_H
		/ (mlx->dist_t);
	line_o = 0;
	draw_single_wall(mlx, line_h, line_o, count);
}

void	casting_rays(int *count, t_mlx *mlx, int tile_dim)
{
	if (++(*count) < VIEWPORT_W)
		mlx->pos.angle += (DGR / (VIEWPORT_W / 60.0)) * (*count);
	if (mlx->pos.angle > 2 * PI)
		mlx->pos.angle -= 2 * PI;
	if (mlx->pos.angle < 0)
		mlx->pos.angle += 2 * PI;
	casting_rays_horizontal(mlx, tile_dim);
	casting_rays_vertical(mlx, tile_dim);
	if (*count < VIEWPORT_W)
		mlx->pos.angle -= (DGR / (VIEWPORT_W / 60.0)) * (*count);
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

int	draw_walls(t_mlx *mlx)
{
	int		count;
	float	diff_a;

	count = -1;
	reset_buffer(mlx);
	mlx->pos.angle -= DGR * 30;
	if (mlx->pos.angle >= 2 * PI)
		mlx->pos.angle -= 2 * PI;
	if (mlx->pos.angle < 0)
		mlx->pos.angle += 2 * PI;
	while (++count < VIEWPORT_W)
	{
		casting_rays(&count, mlx, mlx->images[wall_index(mlx)].i_height);
		check_distance(mlx);
		diff_a = mlx->ray_v.ray.angle - (mlx->pos.angle + DGR * 30);
		if (diff_a < 0)
			diff_a += 2 * PI;
		if (diff_a > 2 * PI)
			diff_a -= 2 * PI;
		mlx->dist_t *= cos(diff_a);
		mlx->dist_h *= cos(diff_a);
		mlx->dist_v *= cos(diff_a);
		draw_lines(mlx, count);
	}
	mlx->pos.angle += DGR * 30;
	return (1);
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
