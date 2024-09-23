/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:38:54 by gsapio            #+#    #+#             */
/*   Updated: 2024/07/01 17:05:10 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_abs(int n)
{
	if (n > 0)
		return (n);
	else
		return (n * (-1));
}

int	ft_round(float x)
{
	float	threshold;

	threshold = (int)x + 0.5;
	if (x > threshold)
		return ((int)x + 1);
	else
		return ((int)x);
}

void	dda_put_pixel_in_image(t_mlx *mlx, int color, t_f_v2 point)
{
	char	*buffer;
	int		yx[2];

	buffer = mlx_get_data_addr(mlx->ceil_floor.img_ptr,
			&mlx->ceil_floor.pixel_bits, &mlx->ceil_floor.line_bytes,
			&mlx->ceil_floor.endian);
	yx[0] = round(point.fy);
	yx[1] = round(point.fx);
	if (yx[0] > VIEWPORT_H)
		yx[0] = VIEWPORT_H;
	put_color_to_pixel(yx, buffer, color, mlx);
}

void	dda(t_v2 vec0, t_v2 vec1, int color, t_mlx *mlx)
{
	t_v2	vdif;
	int		steps;
	t_f_v2	v_inc;
	t_f_v2	point;
	int		i;

	vdif.x = vec1.x - vec0.x;
	vdif.y = vec1.y - vec0.y;
	if (abs(vdif.x) > abs(vdif.y))
		steps = abs(vdif.x);
	else
		steps = abs(vdif.y);
	v_inc.fx = vdif.x / (float)steps;
	v_inc.fy = vdif.y / (float)steps;
	point.fx = vec0.x;
	point.fy = vec0.y;
	i = -1;
	while (++i <= steps)
	{
		dda_put_pixel_in_image(mlx, color, point);
		point.fx += v_inc.fx;
		point.fy += v_inc.fy;
	}
}
