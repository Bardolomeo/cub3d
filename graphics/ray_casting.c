/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:03:38 by bard              #+#    #+#             */
/*   Updated: 2024/07/01 20:21:11 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_swall_loop(t_mlx *mlx, int count, int i, t_texture tex)
{
	make_wall_in_image(mlx, (count), i, tex);
}

void	draw_single_wall(t_mlx *mlx, float line_h, float line_o, int count)
{
	int			i;
	t_texture	tex;

	i = -1;
	tex.ty_off = 0;
	tex.ty_step = mlx->images[wall_index(mlx)].i_height / line_h;
	if (line_h > VIEWPORT_H)
		tex.ty_off = (line_h - VIEWPORT_H) / 2;
	if (line_h > VIEWPORT_H)
		line_h = VIEWPORT_H;
	line_o = (VIEWPORT_H / 2.0) - line_h / 2;
	tex.ty = tex.ty_step * tex.ty_off;
	if (mlx->dist_v < mlx->dist_h)
		tex.tx = (int)(mlx->int_ray.y) % mlx->images[wall_index(mlx)].i_width;
	else
		tex.tx = (int)(mlx->int_ray.x) % mlx->images[wall_index(mlx)].i_width;
	i = line_o;
	while (++i < line_o + line_h)
	{
		draw_swall_loop(mlx, count, i, tex);
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
	if ((*count) < VIEWPORT_W)
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
	return (mlx->pos.angle += DGR * 30, 1);
}
