/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:03:38 by bard              #+#    #+#             */
/*   Updated: 2024/06/01 14:03:27 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>


void	put_color_to_pixel(int *yx, char *buffer, int color, t_mlx *mlx)
{
	int pixel = (yx[0] * mlx->ceil_floor.line_bytes) + (yx[1] * 4);
	if (buffer[pixel] == 0 && buffer[pixel + 1] == 0 && buffer[pixel + 2] == 0 && buffer[pixel + 3] == 0)
	{
		if (mlx->ceil_floor.endian == 1)
		{
		    buffer[pixel + 0] = (color >> 24);
		    buffer[pixel + 1] = (color >> 16) & 0xFF;
		    buffer[pixel + 2] = (color >> 8) & 0xFF;
		    buffer[pixel + 3] = (color) & 0xFF;
		}
		else if (mlx->ceil_floor.endian == 0) 
		{
		    buffer[pixel + 0] = (color) & 0xFF;
		    buffer[pixel + 1] = (color >> 8) & 0xFF;
		    buffer[pixel + 2] = (color >> 16) & 0xFF;
		    buffer[pixel + 3] = (color >> 24);
		}
	}
}

void	draw_ceiling_floor(t_mlx *mlx)
{
	char	*buffer;
	int		yx[2];

	buffer = mlx_get_data_addr(mlx->ceil_floor.img_ptr,
			&mlx->ceil_floor.pixel_bits, &mlx->ceil_floor.line_bytes,
			&mlx->ceil_floor.endian);
	if (mlx->ceil_floor.pixel_bits != 32)
    {
		mlx->ceiling_color = mlx_get_color_value(mlx, mlx->ceiling_color);
		mlx->floor_color = mlx_get_color_value(mlx, mlx->floor_color);
	}
	yx[0] = -1;
	while (++(yx[0]) < VIEWPORT_H)
	{
		yx[1] = -1;
		while (++(yx[1]) < VIEWPORT_W)
		{
			if (yx[0] <= VIEWPORT_H / 2)
				put_color_to_pixel(yx, buffer, mlx->ceiling_color, mlx);
			else
				put_color_to_pixel(yx, buffer, mlx->floor_color, mlx);
		}
	}
}

void	put_walls_texture(t_mlx *mlx)
{
	if ((mlx->pos.angle < PI && mlx->pos.angle >= 0) && mlx->dist_t == mlx->dist_h)
	{
		mlx->walls.buffer = mlx_get_data_addr(mlx->images[SO].img_ptr, &mlx->walls.pixel_bits, &mlx->walls.line_bytes, &mlx->walls.endian);
	}
	if ((mlx->pos.angle > PI / 2 && mlx->pos.angle <= PI_3) && mlx->dist_t == mlx->dist_v)
	{
		mlx->walls.buffer = mlx_get_data_addr(mlx->images[EA].img_ptr, &mlx->walls.pixel_bits, &mlx->walls.line_bytes, &mlx->walls.endian);
	}
	if ((mlx->pos.angle > PI && mlx->pos.angle <= PI * 2) && mlx->dist_t == mlx->dist_h)
	{
		mlx->walls.buffer = mlx_get_data_addr(mlx->images[NO].img_ptr, &mlx->walls.pixel_bits, &mlx->walls.line_bytes, &mlx->walls.endian);
	}
	if ((mlx->pos.angle > PI_3 || mlx->pos.angle <= PI_2) && mlx->dist_t == mlx->dist_v)
	{
		mlx->walls.buffer = mlx_get_data_addr(mlx->images[WE].img_ptr, &mlx->walls.pixel_bits, &mlx->walls.line_bytes, &mlx->walls.endian);
	}
}

int get_pixel(t_mlx *mlx, int px, int py)
{
	int	ind;
	int	c;

	ind = px * 4 + 4 * (mlx->walls.line_bytes / 4) * py;
	c = ((mlx->walls.buffer[ind + 3] << 24)  | (mlx->walls.buffer[ind + 2] << 16) 
		| (mlx->walls.buffer[ind + 1] << 8) | (mlx->walls.buffer[ind]));
	return (c);
} 

void	make_wall_in_image(t_mlx *mlx, int x, int y, int c)
{
	char	*buffer;
	int		yx[2];

	yx[0] = y;
	yx[1] = x;
	buffer = mlx_get_data_addr(mlx->ceil_floor.img_ptr, &mlx->ceil_floor.pixel_bits,
		&mlx->ceil_floor.line_bytes, &mlx->ceil_floor.endian);
	put_color_to_pixel(yx, buffer, c, mlx);
	
}

void	draw_single_wall(t_mlx *mlx, float line_h, float line_o, int count)
{
	int i = -1;
	int j = -1;
	int	ty;
	int	ty_step;
	int	c;

	ty_step = (mlx->walls.line_bytes/4) / line_h;
	ty = 0;
	if (line_h > VIEWPORT_H)
		line_h = VIEWPORT_H;
	line_o = (VIEWPORT_H / 2) - line_h / 2;
	i = line_o;
	while (++i < line_o + line_h)
	{
		j = -1;
		while (++j < 2)
		{
			// c = get_pixel(mlx, (int)(j), (int)(ty));
			if (mlx->dist_t == mlx->dist_v)
				c = 0x00aa0000;
			else
				c = 0x00ff0000;
			make_wall_in_image(mlx, j + (count), i, c);
		}
		ty += ty_step;
	}
}

void	draw_lines(t_mlx *mlx, int count)
{
	int		i;
	int		j;
	float	line_o;
	float	line_h;

	count_cols_rows(&i, &j, mlx->map);
	line_h = (TILE_DIM)*VIEWPORT_H / (mlx->dist_t);
	line_o = 0; 
	put_walls_texture(mlx);
	draw_single_wall(mlx, line_h, line_o, count);
}

void	casting_rays(int *count, t_mlx *mlx)
{
	if (++(*count) < VIEWPORT_W)
		mlx->pos.angle += (DGR / (VIEWPORT_W / 60.0)) * (*count);
	if (mlx->pos.angle > 2 * PI)
		mlx->pos.angle -= 2 * PI;
	if (mlx->pos.angle < 0)
		mlx->pos.angle += 2 * PI;
	casting_rays_horizontal(mlx);
	casting_rays_vertical(mlx);
	if (*count < VIEWPORT_W)
		mlx->pos.angle -= (DGR / (VIEWPORT_W / 60.0)) * (*count);
	if (*count == VIEWPORT_W)
		*count = -1;
}

void	empty_buffer(t_mlx *mlx)
{
	char *buffer;
	int		i = 0;

	buffer = mlx_get_data_addr(mlx->ceil_floor.img_ptr, 
		&mlx->ceil_floor.pixel_bits, &mlx->ceil_floor.line_bytes, &mlx->ceil_floor.endian);
	while (i < VIEWPORT_H * VIEWPORT_W * 4)
	{
		buffer[i] = 0;
		i++;
	}
}


void	check_distance(t_mlx *mlx, int *color)
{
	if (mlx->dist_h > mlx->dist_v)
	{
		mlx->int_ray.x = mlx->ray_v.ray.fx;
		mlx->int_ray.y = mlx->ray_v.ray.fy;
		mlx->dist_t = mlx->dist_v;
		*color = 0xaa0000;
	}
	else
	{
		mlx->int_ray.x = mlx->ray_h.ray.fx;
		mlx->int_ray.y = mlx->ray_h.ray.fy;
		mlx->dist_t = mlx->dist_h;
		*color = 0xee0000;
	}
}

int	draw_walls(t_mlx *mlx)
{
	int			count;
	int			color;
	float		diff_a;


	count = -1;
	empty_buffer(mlx);
	mlx->pos.angle -= DGR * 30;
	if (mlx->pos.angle >= 2 * PI)
		mlx->pos.angle -= 2 * PI;
	while (++count < 960)
	{
		casting_rays(&count, mlx);
		check_distance(mlx, &color);
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
	draw_ceiling_floor(mlx);
	return (1);
}

int	draw_minimap(t_mlx *mlx)
{
	static int	count = -1;
	int	color;

	mlx->pos.angle -= DGR * 30;
	if (mlx->pos.angle >= 2 * PI)
		mlx->pos.angle -= 2 * PI;
	casting_rays(&count, mlx);
	check_distance(mlx, &color);
	if (count == VIEWPORT_W)
		count = -1;
	mlx->pos.angle += DGR *30;
	draw_map(mlx);
	DDA(mlx->pos, mlx->int_ray, 0x00ffff, mlx);
	draw_player_loop(mlx);
	return (1);
}
