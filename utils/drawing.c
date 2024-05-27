/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:08:27 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/27 20:13:51 by gsapio           ###   ########.fr       */
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
		vector.angle = PI_2;
	else if (mlx->map[i][j] == 'W')
		vector.angle = 0;
	else if (mlx->map[i][j] == 'E')
		vector.angle = PI;
	else if (mlx->map[i][j] == 'S')
		vector.angle = PI_3;
	vector.x *= TILE_DIM;
	vector.y *= TILE_DIM;
	return (vector);
}

void	draw_tile(int color, int i, int j, t_mlx *mlx)
{
	int	oi = 0;
	int	oj = 0;
	
	while (oi < TILE_DIM - 1)
	{
		oj = 0;
		while (oj < TILE_DIM - 1)
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
	if (ox == (PLAYER_DIM / 2) || ox == -(PLAYER_DIM / 2))
	{
		oy++;
		ox = -PLAYER_DIM;
	}
	if (oy == (PLAYER_DIM / 2) || oy == -(PLAYER_DIM / 2))
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