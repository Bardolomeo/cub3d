/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:55:54 by gsapio            #+#    #+#             */
/*   Updated: 2024/06/20 16:34:58 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#include "minilibx-linux/mlx.h"


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

void	init_elements(t_mlx *mlx)
{
	int	i;

	i = 0;
	mlx->ceiling_color = -1;
	mlx->floor_color = -1;
	mlx->map = NULL;
	while (i < 4)
	{
		mlx->images[i].img_ptr = NULL;
		i++;
	}
	mlx->ceil_floor.img_ptr = NULL;
	mlx->walls.img_ptr = NULL;
	mlx->pos.x = 0;
	mlx->pos.y = 0;
	mlx->dir.x = 16;
	mlx->dir.y = 16;
	mlx->keys.w = 0;
	mlx->keys.n = 0;
	mlx->keys.s = 0;
	mlx->keys.e = 0;
	mlx->keys.f = 0;
	mlx->keys.c = 0;
}


void	on_game_start(t_mlx *mlx)
{
	mlx->pos.x = player_pos(mlx).x;
	mlx->pos.y = player_pos(mlx).y;
	mlx->pos.angle = player_pos(mlx).angle;
	mlx->ceil_floor.img_ptr = mlx_new_image(mlx->mlx_ptr, VIEWPORT_W,
			VIEWPORT_H);
	draw_ceiling_floor(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->ceil_floor.img_ptr, 0, 0);
}


int	key_down(int keycode, t_mlx *mlx)
{
	float pdy;
	float pdx;
	
	pdy = 0.0;
	pdx = 0.0;
	on_rotate(mlx, keycode);
	compute_direction(mlx, &pdx, &pdy);
	on_move(mlx, keycode, pdy, pdx);
	draw_walls(mlx);
	draw_minimap(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->ceil_floor.img_ptr, 0,0);
	return (0);
}

int	mouse_move(int x, int y, t_mlx *mlx)
{
	static int	last_x = -1;
	static int	counter = 0;
	
	y = y;
	counter++;
	printf("%d, x:%d, y:%d\n", counter, x, y);
	if (counter >= 5)
	{
		if (last_x == x)
			return (0);
		if (x > last_x)
		{
			mlx->pos.angle += (3 * DGR);
			if (mlx->pos.angle > 2 * PI)
				mlx->pos.angle -= 2 * PI;
		}
		else if (x < last_x)
		{
			mlx->pos.angle -= (3 * DGR);
			if (mlx->pos.angle < 0)
				mlx->pos.angle += 2 * PI;
		}
		last_x = x;
		draw_walls(mlx);
		draw_minimap(mlx);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->ceil_floor.img_ptr, 0,0);
		counter = 0;
	}
	return (0);
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
	mlx_hook(mlx.mlx_win, 2, (1L<<0), key_down, &mlx);
	mlx_hook(mlx.mlx_win, 6, (1L<<6), mouse_move, &mlx);
	// mlx_loop_hook(mlx.mlx_ptr, draw_minimap, &mlx);
	mlx_loop(mlx.mlx_ptr);
	destroy_game(&mlx);
	return (0);
}
