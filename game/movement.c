/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:27:38 by bard              #+#    #+#             */
/*   Updated: 2024/07/04 17:55:06 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_up(t_mlx *mlx, int keycode, float pdy, float pdx)
{
	if (keycode == 'w')
	{
		if (mlx->map[(int)(mlx->pos.y + round(pdy)
				* 1.1) >> (int)log2(TILE_DIM)][(int)(mlx->pos.x + round(pdx)
				* 1.1) >> (int)log2(TILE_DIM)] != '1')
		{
			mlx->pos.y += round(pdy);
			mlx->pos.x += round(pdx);
		}
	}
}

void	move_down(t_mlx *mlx, int keycode, float pdy, float pdx)
{
	if (keycode == 's')
	{
		if (mlx->map[(int)(mlx->pos.y - round(pdy)
				* 1.1) >> (int)log2(TILE_DIM)][(int)(mlx->pos.x - round(pdx)
				* 1.1) >> (int)log2(TILE_DIM)] != '1')
		{
			mlx->pos.y -= round(pdy);
			mlx->pos.x -= round(pdx);
		}
	}
}

void	on_move(t_mlx *mlx, int keycode, float pdy, float pdx)
{
	move_up(mlx, keycode, pdy, pdx);
	move_down(mlx, keycode, pdy, pdx);
	if (keycode == 'a')
	{
		if (mlx->map[(int)(mlx->pos.y - round(pdx)
				* 1.1) >> (int)log2(TILE_DIM)][(int)(mlx->pos.x + round(pdy)
				* 1.1) >> (int)log2(TILE_DIM)] != '1')
		{
			mlx->pos.y -= round(pdx);
			mlx->pos.x += round(pdy);
		}
	}
	if (keycode == 'd')
	{
		if (mlx->map[(int)(mlx->pos.y + round(pdx)
				* 1.1) >> (int)log2(TILE_DIM)][(int)(mlx->pos.x - round(pdy)
				* 1.1) >> (int)log2(TILE_DIM)] != '1')
		{
			mlx->pos.y += round(pdx);
			mlx->pos.x -= round(pdy);
		}
	}
}

void	on_rotate(t_mlx *mlx, int keycode)
{
	if (keycode == 65361)
		mlx->pos.angle -= (3 * DGR);
	if (keycode == 65363)
		mlx->pos.angle += (3 * DGR);
	if (mlx->pos.angle < 0)
		mlx->pos.angle += (PI * 2);
	if (mlx->pos.angle >= (PI * 2))
		mlx->pos.angle -= PI * 2;
}

void	compute_direction(t_mlx *mlx, float *pdx, float *pdy)
{
	*pdy = sin(mlx->pos.angle) * 5;
	*pdx = cos(mlx->pos.angle) * 5;
	if (mlx->pos.angle == (float)(PI / 2) || mlx->pos.angle == (float)(PI / 2
			* 3))
		*pdx = 0;
	if (mlx->pos.angle == (float)(PI) || mlx->pos.angle == 0)
		*pdy = 0;
}
