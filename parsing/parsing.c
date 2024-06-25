/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:41:48 by gsapio            #+#    #+#             */
/*   Updated: 2024/06/25 16:10:38 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_positioning(int i, t_mlx *mlx, char *str)
{
	if (ft_strncmp(str + i, "NO ", 3) == 0 && mlx->keys.n == 0)
	{
		set_image(str + i + 3, &mlx->images[NO], mlx);
		mlx->keys.n = 1;
	}
	else if (ft_strncmp(str + i, "SO ", 3) == 0 && mlx->keys.s == 0)
	{
		set_image(str + i + 3, &mlx->images[SO], mlx);
		mlx->keys.s = 1;
	}
	else if (ft_strncmp(str + i, "WE ", 3) == 0 && mlx->keys.w == 0)
	{
		set_image(str + i + 3, &mlx->images[WE], mlx);
		mlx->keys.w = 1;
	}
	else if (ft_strncmp(str + i, "EA ", 3) == 0 && mlx->keys.e == 0)
	{
		set_image(str + i + 3, &mlx->images[EA], mlx);
		mlx->keys.e = 1;
	}
	else
		return (0);
	return (1);
}

int	parse_file(int argc, char **argv, t_mlx *mlx)
{
	int	fd;

	fd = -2;
	if (argc != 2)
		perror("Error");
	else if (!ft_strrchr(argv[1], '.'))
		perror("Error");
	else if (ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 5))
		perror("Error\n");
	else if (!check_elements(fd, argv, mlx))
		perror("Error");
	else if (!map_manager(fd, argv, mlx))
		perror("Error");
	else
		return (1);
	return (0);
}
