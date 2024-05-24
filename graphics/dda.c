/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:38:54 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/22 16:27:13 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Function for finding absolute value 
int ft_abs(int n) 
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

// DDA Function for line generation 
void DDA(t_v2 vec0, t_v2 vec1, t_mlx *mlx) 
{ 
	// calculate dx & dy 
	t_v2	vdif;
	int		steps; 
	t_f_v2	vInc;
	t_f_v2	point;

	vdif.x = vec1.x - vec0.x;
	vdif.y = vec1.y - vec0.y;
	// calculate steps required for generating pixels 
	if (abs(vdif.x) > abs(vdif.y))
		steps = abs(vdif.x);
	else
		steps = abs(vdif.y);
	
	// calculate increment in x & y for each steps
	vInc.fx = vdif.x / (float)steps;
	vInc.fy = vdif.y / (float)steps;
	
	// Put pixel for each step 
	point.fx = vec0.x; 
	point.fy = vec0.y; 
	for (int i = 0; i <= steps; i++) {
		mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win,
				ft_round(point.fx), ft_round(point.fy), 0xffffff); 
		point.fx += vInc.fx; // increment in x at each step 
		point.fy += vInc.fy; // increment in y at each step 
			 // for visualization of line- 
	} 
}