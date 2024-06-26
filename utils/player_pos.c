/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:02:28 by mtani             #+#    #+#             */
/*   Updated: 2024/06/26 18:53:57 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_player_in_map(char **map, int *i, int *j, t_v2 *vector)
{
	*i = -1;
	while (map[++(*i)])
	{
		*j = -1;
		while (map[*i][++(*j)])
		{
			if (valid_player(map[*i][*j]))
			{
				vector->x = (*j);
				vector->y = (*i);
				return ;
			}
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
		vector.angle = PI;
	else if (mlx->map[i][j] == 'E')
		vector.angle = 0;
	else if (mlx->map[i][j] == 'S')
		vector.angle = PI_2;
	vector.x = vector.x * TILE_DIM + TILE_DIM / 2;
	vector.y = vector.y * TILE_DIM + TILE_DIM / 2;
	return (vector);
}
