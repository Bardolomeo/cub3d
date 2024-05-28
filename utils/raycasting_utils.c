/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:38:24 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/28 17:51:26 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	dist(t_v2 player, t_f_v2 ray)
{
	float		h_comp;
	float		v_comp;
	float	dist;

	h_comp = player.x - ray.fx;
	v_comp = player.y - ray.fy;
	dist = sqrt((h_comp * h_comp) + (v_comp * v_comp));
	return (dist);
}

int	float_comp(float first, float second)
{
    float	diff;
	float	largest;
	
	diff = fabs(first - second);
    first = fabs(first);
    second = fabs(second);
	if (second > first)
		largest = second;
	else
		largest = first;
    if (diff <= largest * 0.0001)
	{
        return (1);
	}
	if (diff < 0.0001 && second == 0)
		return (1);
    return (0);
}