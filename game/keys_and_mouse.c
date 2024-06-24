/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_and_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:28:37 by gsapio            #+#    #+#             */
/*   Updated: 2024/06/24 20:10:46 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouse_single_rotation(int x, int *last_x, t_mlx *mlx, int *counter)
{
	if (x > *last_x)
	{
		mlx->pos.angle += (3 * DGR);
		if (mlx->pos.angle > 2 * PI)
			mlx->pos.angle -= 2 * PI;
	}
	else if (x < *last_x)
	{
		mlx->pos.angle -= (3 * DGR);
		if (mlx->pos.angle < 0)
			mlx->pos.angle += 2 * PI;
	}
	*last_x = x;
	draw_walls(mlx);
	draw_minimap(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->ceil_floor.img_ptr,
		0, 0);
	*counter = 0;
}

int	mouse_move(int x, int y, t_mlx *mlx)
{
	static int	last_x = -1;
	static int	counter = 0;

	(void)y;
	if (mlx->mouse_down == 0)
		return (0);
	counter++;
	if (counter >= 5)
	{
		if (last_x == x)
			return (0);
		mouse_single_rotation(x, &last_x, mlx, &counter);
	}
	return (0);
}

int	key_down(int keycode, t_mlx *mlx)
{
	float	pdy;
	float	pdx;

	pdy = 0.0;
	pdx = 0.0;
	on_rotate(mlx, keycode);
	compute_direction(mlx, &pdx, &pdy);
	on_move(mlx, keycode, pdy, pdx);
	draw_walls(mlx);
	draw_minimap(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->ceil_floor.img_ptr,
		0, 0);
	return (0);
}

int	mouse_press_hook(int keycode, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (keycode == 3)
		mlx->mouse_down = 1;
	return (0);
}

int	mouse_release_hook(int keycode, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (keycode == 3)
		mlx->mouse_down = 0;
	return (0);
}
