/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:55:54 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/22 14:17:19 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#include "minilibx-linux/mlx.h"

char	**free_matrix(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		free(map[i++]);
	free (map);
	return (NULL);
}

int	handler_func(t_mlx *mlx)
{
	mlx_loop_end(mlx->mlx_ptr);
	return (0);
}

int	key_func(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
		handler_func(mlx);
	// printf("keycode: %d\n", keycode);
	// printf("letter: %c\n", keycode + 106);
	if (keycode == 'w')
	{
	}
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
	mlx->pos.x = 2;
	mlx->pos.y = 2;
	mlx->dir.x = 16;
	mlx->dir.y = 16;
}

int	draw_pixels(t_mlx *mlx)
{
	DDA(mlx->pos, mlx->dir, mlx);
	mlx->dir.x += 10;
	mlx->dir.y += 10;
	return (0);
}
// void	print_elements(t_mlx *mlx)
// {
// 	int	i;

// 	i = -1;
// 	printf("ceiling color: %d\n", mlx->ceiling_color);
// 	printf("floor color: %d\n", mlx->floor_color);
// 	while (++i < 4)
// 	{
// 		printf("image ptr: %p    h: %d    w: %d\n", mlx->images[i].img_ptr, mlx->images[i].i_height, mlx->images[i].i_width);
// 	}
// }

// void	print_map(t_mlx *mlx)
// {
// 	int	i;

// 	i = 0;
// 	while(mlx->map[i])
// 	{
// 		printf("%s\n", mlx->map[i]);
// 		i++;
// 	}	
// }


int	main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	init_elements(&mlx);
	if (!parse_file(argc, argv, &mlx))
		return (0);
	mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, 640, 480, "Vermin");
	mlx_hook(mlx.mlx_win, 17, 1L << 2, handler_func, &(mlx.mlx_ptr));
	mlx_key_hook(mlx.mlx_win, key_func, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, draw_pixels, &mlx);
	mlx_loop(mlx.mlx_ptr);
	destroy_game(&mlx);
	return (0);
}
