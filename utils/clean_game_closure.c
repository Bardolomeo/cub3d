/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_game_closure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:03:49 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/20 16:47:20 by gsapio           ###   ########.fr       */
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