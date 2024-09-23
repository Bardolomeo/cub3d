/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:08:27 by gsapio            #+#    #+#             */
/*   Updated: 2024/06/25 16:02:46 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_tile(int color, int i, int j, t_mlx *mlx)
{
	int		oi;
	int		oj;
	char	*buffer;
	int		yx[2];

	oi = 0;
	oj = 0;
	buffer = mlx_get_data_addr(mlx->ceil_floor.img_ptr,
			&mlx->ceil_floor.pixel_bits, &mlx->ceil_floor.line_bytes,
			&mlx->ceil_floor.endian);
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
	int		yx[2];
	char	*buffer;

	oy = -PLAYER_DIM;
	buffer = mlx_get_data_addr(mlx->ceil_floor.img_ptr,
			&mlx->ceil_floor.pixel_bits,
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
