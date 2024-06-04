/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bard <bard@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:38:54 by gsapio            #+#    #+#             */
/*   Updated: 2024/06/04 05:19:13 by bard             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Function for finding absolute value
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
	
	buffer = mlx_get_data_addr(mlx->ceil_floor.img_ptr, &mlx->ceil_floor.pixel_bits,
			&mlx->ceil_floor.line_bytes, &mlx->ceil_floor.endian);
	yx[0] = round(point.fy);
	yx[1] = round(point.fx);
	put_color_to_pixel(yx, buffer, color, mlx);
}

void	DDA(t_v2 vec0, t_v2 vec1, int color, t_mlx *mlx)
{
	t_v2 vdif; // DDA Function for line generation
	int steps;
	t_f_v2 vInc;
	t_f_v2 point;
	int i;

	vdif.x = vec1.x - vec0.x; // calculate dx & dy
	vdif.y = vec1.y - vec0.y;
	if (abs(vdif.x) > abs(vdif.y)) // calculate steps required for generating pixels
		steps = abs(vdif.x);
	else
		steps = abs(vdif.y);
	vInc.fx = vdif.x / (float)steps; // calculate increment in x & y for each steps
	vInc.fy = vdif.y / (float)steps; // Put pixel for each step
	point.fx = vec0.x;
	point.fy = vec0.y;
	i = -1;
	while (++i <= steps)
	{
		dda_put_pixel_in_image(mlx, color, point);
		point.fx += vInc.fx; // increment in x at each step
		point.fy += vInc.fy; // increment in y at each step
	}
}
