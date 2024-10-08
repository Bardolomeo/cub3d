/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:52:43 by gsapio            #+#    #+#             */
/*   Updated: 2024/06/27 16:19:58 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int	valid_chars(char tile)
{
	if (tile == '1' || tile == '0' || tile == 'N' || tile == 'W' || tile == 'E'
		|| tile == 'S')
		return (1);
	return (0);
}

int	valid_tile(char **map, int i, int j)
{
	if (!valid_chars(map[i + 1][j]) || !valid_chars(map[i - 1][j])
		|| !valid_chars(map[i][j - 1]) || !valid_chars(map[i][j + 1])
		|| !valid_chars(map[i - 1][j - 1]) || !valid_chars(map[i + 1][j - 1])
		|| !valid_chars(map[i - 1][j + 1]) || !valid_chars(map[i + 1][j + 1]))
		return (0);
	return (1);
}

int	valid_player(char tile)
{
	if (tile == 'N' || tile == 'W' || tile == 'S' || tile == 'E')
		return (1);
	return (0);
}

void	count_cols_rows(int *i, int *j, char **map)
{
	int	max_i;
	int	max_j;

	*i = -1;
	max_i = 0;
	max_j = 0;
	while (map[++(*i)])
	{
		if (*i > max_i)
			max_i = *i;
		*j = 0;
		while (map[*i][*j])
			(*j)++;
		if (*j > max_j)
			max_j = *j;
	}
	*i = max_i;
	*j = max_j;
	return ;
}
