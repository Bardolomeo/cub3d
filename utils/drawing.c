/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bard <bard@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:27:33 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/23 15:00:22 by bard             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_player_in_map(char **map, int *i, int *j, t_v2 *vector)
{
	*i= -1;
	while (map[++(*i)])
	{
		*j = -1;
		while (map[*i][++(*j)])
			if (valid_player(map[*i][*j]))
			{
				vector->x = (*j);
				vector->y = (*i);
				return ;
			}
	}
}

t_v2	player_pos(t_mlx *mlx)
{
	t_v2	vector;
	int		i;
	int		j;

	find_player_in_map(mlx->map, &i, &j, &vector);
	if (mlx->map[i][j] == 'N')
		vector.angle = PI / 2;
	else if (mlx->map[i][j] == 'W')
		vector.angle = 0;
	else if (mlx->map[i][j] == 'E')
		vector.angle = PI;
	else if (mlx->map[i][j] == 'S')
		vector.angle = (PI * 3) / 4;
	vector.x *= TILE_DIM;
	vector.y *= TILE_DIM;
	return (vector);
}

void	draw_tile(int color, int i, int j, t_mlx *mlx)
{
	int	oi = 0;
	int	oj = 0;
	
	while (oi < TILE_DIM)
	{
		oj = 0;
		while (oj < TILE_DIM)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win,
						j*TILE_DIM + oj, i*TILE_DIM + oi, color);
			oj++;
		}
		oi++;
	}
}

int	draw_player_loop(t_mlx *mlx)
{
	static int	ox = -PLAYER_DIM;
	static int	oy = -PLAYER_DIM;

	mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, 
		mlx->pos.x + ox, mlx->pos.y + oy, 0xff0000);
	if (ox == PLAYER_DIM - 1)
	{
		oy++;
		ox = -PLAYER_DIM;
	}
	if (oy == PLAYER_DIM - 1)
		oy = 0;
	ox++;
	return (1);
}


int	draw_player_iterative(t_mlx *mlx)
{
	int	ox;
	int	oy;

	oy = -PLAYER_DIM;
	while (oy < PLAYER_DIM)
	{
		ox = -PLAYER_DIM;
		while (ox < PLAYER_DIM)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, 
				mlx->pos.x + ox, mlx->pos.y + oy, 0xff0000);	
			ox++;
		}
		oy++;
	}
	return (1);
}

int	draw_map(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (mlx->map[++i])
	{
		j = -1;
		while (mlx->map[i][++j])
		{
			if (mlx->map[i][j] == '1')
				draw_tile(0x00ff00, i, j, mlx);
			if (mlx->map[i][j] == '0' || valid_player(mlx->map[i][j]))
				draw_tile(0x0000ff, i, j, mlx);
		}
	}
	return (0);
}