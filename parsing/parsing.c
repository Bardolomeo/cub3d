/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:41:48 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/22 18:30:23 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <fcntl.h>

int	parse_file(int argc, char **argv, t_mlx *mlx)
{
	int	fd;

	fd = -2;
	if (argc != 2)
		perror("Error");
	else if (!ft_strchr(argv[1], '.'))
		perror("Error");
	else if (ft_strncmp(ft_strchr(argv[1], '.'), ".cub", 5))
		perror("Error\n");
	else if (!check_elements(fd, argv, mlx))
		perror("Error");
	else if (!map_manager(fd, argv, mlx))
		perror("Error");
	else
		return (1);
	return (0);
}
