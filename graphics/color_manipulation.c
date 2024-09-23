/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:51:47 by gsapio            #+#    #+#             */
/*   Updated: 2024/07/05 15:39:14 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_color_to_pixel(int yx[2], char *buffer, int color, t_mlx *mlx)
{
	int	pixel;

	pixel = (yx[0] * mlx->ceil_floor.line_bytes) + (yx[1] * 4);
	if (pixel < 0)
		return ;
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

void	put_background_to_image(int *yx, char *buffer, int color, t_mlx *mlx)
{
	int	pixel;
	int	color2;

	pixel = (yx[0] * mlx->ceil_floor.line_bytes) + (yx[1] * 4);
	color2 = (buffer[pixel + 3] >> 24 | (buffer[pixel
				+ 2] >> 16 & 0xFF) | (buffer[pixel
				+ 1] >> 8 & 0xFF) | (buffer[pixel + 0] & 0xFF));
	if (color2 == color)
		return ;
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

void	reset_buffer(t_mlx *mlx)
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
				put_background_to_image(yx, buffer, mlx->ceiling_color, mlx);
			else
				put_background_to_image(yx, buffer, mlx->floor_color, mlx);
		}
	}
}

int	get_pixel(t_mlx *mlx, int px, int py)
{
	int	ind;
	int	c;

	ind = px * 4 + 4 * (mlx->walls.line_bytes / 4) * py;
	c = ((mlx->walls.buffer[ind + 3] << 24) | (mlx->walls.buffer[ind
				+ 2] << 16) | (mlx->walls.buffer[ind
				+ 1] << 8) | (mlx->walls.buffer[ind]));
	return (c);
}

void	put_color_to_wall(t_mlx *mlx, int *yx, char *buffer[2], int ind[2])
{
	if (mlx->ray_h.dof == MAX_DOF || mlx->ray_v.dof == MAX_DOF)
	{
		if (yx[0] < VIEWPORT_H / 2)
			put_color_to_pixel(yx, buffer[0], mlx->ceiling_color, mlx);
		else
			put_color_to_pixel(yx, buffer[0], mlx->floor_color, mlx);
		return ;
	}
	if (mlx->dist_t == mlx->dist_v)
		put_color_to_pixel(yx, buffer[0],
			((((buffer[1][ind[1]] & 0xFF) | (buffer[1][ind[1]
							+ 1] & 0xFF) << 8 | (buffer[1][ind[1]
							+ 2] & 0xFF) << 16) >> 1) & 0x7F7F7F), mlx);
	else
		put_color_to_pixel(yx, buffer[0],
			((buffer[1][ind[1]] & 0xFF) | (buffer[1][ind[1] + 1] & 0xFF)
				<< 8 | (buffer[1][ind[1] + 2] & 0xFF) << 16), mlx);
}
