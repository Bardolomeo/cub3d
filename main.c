/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:55:54 by gsapio            #+#    #+#             */
/*   Updated: 2024/06/26 17:58:42 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	handler_func(t_mlx *mlx)
{
	mlx_loop_end(mlx->mlx_ptr);
	return (0);
}

int	key_func(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
		handler_func(mlx);
	return (0);
}

void	on_game_start(t_mlx *mlx)
{
	mlx->pos.x = player_pos(mlx).x;
	mlx->pos.y = player_pos(mlx).y;
	mlx->pos.angle = player_pos(mlx).angle;
	mlx->ceil_floor.img_ptr = mlx_new_image(mlx->mlx_ptr, VIEWPORT_W,
			VIEWPORT_H);
	reset_buffer(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->ceil_floor.img_ptr,
		0, 0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	init_elements(&mlx);
	if (!parse_file(argc, argv, &mlx))
		return (0);
	mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, VIEWPORT_W, VIEWPORT_H, "Vermin");
	on_game_start(&mlx);
	mlx_hook(mlx.mlx_win, 17, 1L << 2, handler_func, &(mlx.mlx_ptr));
	mlx_key_hook(mlx.mlx_win, key_func, &mlx);
	mlx_hook(mlx.mlx_win, 2, (1L << 0), key_down, &mlx);
	mlx_hook(mlx.mlx_win, 4, (1L << 2), mouse_press_hook, &mlx);
	mlx_hook(mlx.mlx_win, 5, (1L << 3), mouse_release_hook, &mlx);
	mlx_hook(mlx.mlx_win, 6, (1L << 6), mouse_move, &mlx);
	mlx_loop(mlx.mlx_ptr);
	destroy_game(&mlx);
	return (0);
}
