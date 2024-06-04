/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bard <bard@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:08:27 by gsapio            #+#    #+#             */
/*   Updated: 2024/06/04 08:35:48 by bard             ###   ########.fr       */
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
		vector.angle = PI_3;
	else if (mlx->map[i][j] == 'W')
		vector.angle = 0;
	else if (mlx->map[i][j] == 'E')
		vector.angle = PI;
	else if (mlx->map[i][j] == 'S')
		vector.angle = PI_2;
	vector.x = vector.x * TILE_DIM + TILE_DIM / 2;
	vector.y = vector.y * TILE_DIM + TILE_DIM / 2;
	return (vector);
}

void	draw_tile(int color, int i, int j, t_mlx *mlx)
{
	int		oi = 0;
	int		oj = 0;
	char	*buffer;
	int		yx[2];
	
	buffer = mlx_get_data_addr(mlx->ceil_floor.img_ptr, &mlx->ceil_floor.pixel_bits,
				&mlx->ceil_floor.line_bytes, &mlx->ceil_floor.endian);
	while (oi < mlx->images[wall_index(mlx)].i_height / 8 - 1)
	{
		oj = 0;
		while (oj < mlx->images[wall_index(mlx)].i_height / 8 - 1)
		{
			yx[0] = i * mlx->images[wall_index(mlx)].i_height / 8 + oi;
			yx[1] = j * mlx->images[wall_index(mlx)].i_height / 8 + oj;
			put_color_to_pixel(yx, buffer, color, mlx);
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
	int		ox;
	int		oy;
	int 	yx[2];
	char	*buffer;

	oy = -PLAYER_DIM;
	buffer = mlx_get_data_addr(mlx->ceil_floor.img_ptr, &mlx->ceil_floor.pixel_bits,
			&mlx->ceil_floor.line_bytes, &mlx->ceil_floor.endian);
	while (oy < PLAYER_DIM)
	{
		ox = -PLAYER_DIM;
		while (ox < PLAYER_DIM)
		{
			yx[0] = mlx->pos.y + oy;
			yx[1] = mlx->pos.x + ox;
			put_color_to_pixel(yx, buffer, 0x00ff0000, mlx);
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
				draw_tile(0xffffff, i, j, mlx);
			if (mlx->map[i][j] == '0' || valid_player(mlx->map[i][j]))
				draw_tile(0x000000, i, j, mlx);
		}
	}
	draw_player_iterative(mlx);
	return (0);
}