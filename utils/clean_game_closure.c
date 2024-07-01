/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_game_closure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:03:49 by gsapio            #+#    #+#             */
/*   Updated: 2024/07/01 19:40:12 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	destroy_game(t_mlx *mlx)
{
	int	i;

	mlx_loop_end(mlx->mlx_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	i = -1;
	while (++i < 4 && mlx->images[i].img_ptr != NULL)
		mlx_destroy_image(mlx->mlx_ptr, mlx->images[i].img_ptr);
	ft_free_matrix((void **)mlx->map);
	mlx_destroy_image(mlx->mlx_ptr, mlx->ceil_floor.img_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	return (0);
}

int	destroy_game_on_start(t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (mlx->images[i].img_ptr != NULL)
			mlx_destroy_image(mlx->mlx_ptr, mlx->images[i].img_ptr);
	ft_free_matrix((void **)mlx->map);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	return (0);
}

int	error_fclose(int *fd)
{
	close(*fd);
	return (0);
}

void	init_elementstwo(t_mlx *mlx)
{
	mlx->dist_t = 0;
	mlx->dist_v = 0;
	mlx->dist_h = 0;
	mlx->int_ray.angle = 0;
	mlx->render_flag = 0.0;
	mlx->keys.w = 0;
	mlx->keys.n = 0;
	mlx->keys.s = 0;
	mlx->keys.e = 0;
	mlx->keys.f = 0;
	mlx->keys.c = 0;
	mlx->mouse_down = 0;
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
	init_elementstwo(mlx);
}
