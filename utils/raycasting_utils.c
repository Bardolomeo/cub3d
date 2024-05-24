/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:38:24 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/24 18:38:34 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	dist(t_v2 player, t_f_v2 ray)
{
	int		h_comp;
	int		v_comp;
	float	dist;

	h_comp = abs((int)(player.x - ray.fx));
	v_comp = abs((int)(player.y - ray.fy));
	dist = sqrt((h_comp * h_comp) + (v_comp * v_comp));
	return (dist);
}