/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:55:54 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/14 17:16:02 by mtani            ###   ########.fr       */
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

int	destroy_game(t_mlx *mlx)
{
	// int	i;

	mlx_loop_end(mlx->mlx_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	// i = -1;
	// while (mlx->images[++i].img_ptr != NULL)
	// 	mlx_destroy_image(mlx->mlx_ptr, mlx->images[i].img_ptr);
	// free_matrix(mlx->map);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	return (0);
}

int	handler_func(t_mlx *mlx)
{
	mlx_loop_end(mlx->mlx_ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	(void)argc;
	if (!argv)
		printf ("amazing");
	if (!parse_elements(argc, argv, &mlx))
		return (0);
	mlx.mlx_ptr = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, 1920, 1080, "Vermin");
	mlx_hook(mlx.mlx_win, 17, 1L << 2, handler_func, &(mlx.mlx_ptr));
	mlx_loop(mlx.mlx_ptr);
	destroy_game(&mlx);
	return (0);
}
