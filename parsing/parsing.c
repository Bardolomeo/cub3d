/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:41:48 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/14 16:45:49 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <fcntl.h>
#include <stdio.h>

int	check_map(int fd, char **argv, t_mlx *mlx)
{
}

void	clean_exit()
{

}

void skip_spaces(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i] == ' ' || (*str)[i] == '\t')
		i++;
}

int	get_texture(char *str, t_mlx *mlx)
{
	skip_spaces(&str);
	if (ft_strncmp(str, "NO ", 3) == 0)
		set_image(str + 3, mlx->images[NO]);
	else if (ft_strncmp(str, "SO ", 3) == 0)
		set_image(str + 3, mlx->images[SO]);
	else if (ft_strncmp(str, "WE ", 3) == 0)
		set_image(str + 3, mlx->images[WE]);
	else if (ft_strncmp(str, "EA ", 3) == 0)
		set_image(str + 3, mlx->images[EA]);
	else if (ft_strncmp(str, "F ", 2) == 0)
		set_color(str + 2, mlx->floor_color);
	else if (ft_strncmp(str, "C ", 2) == 0)
		set_color(str + 2, mlx->ceiling_color);
	else if (*str == '\n' || *str == '1')
		return (1);
	else
	{
		free_elements(mlx);
		return (0);
	}
	return (1);
}

int	check_elements(int fd, char **argv, t_mlx *mlx)
{
	char	*temp;

	fd = open(argv[1], O_RDONLY);
	temp = get_next_line(fd);
	if (!temp)
	{
		perror("Error\n");
		close(fd);
		return (0);
	}
	while (temp != NULL)
	{
		if (!get_texture(temp, mlx))
			return (0);
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
	if (!check_all_elements())
	{
		perror("Error\n");
		return (0);
	}
	return (1);
}

int	parse_elements(int argc, char **argv, t_mlx *mlx)
{
	char	*extension;
	int		fd;

	fd = -2;
	if (argc != 2)
		perror("Wrong number of arguments\n");
	else if (ft_strncmp(ft_strchr(argv[0], '.'), ".cub", 5))
		perror("Invalid file extension\n");
	else if (!check_elements(fd, argv, mlx))
		perror("Invalid configuration\n");
	else if (!check_map(fd, argv, mlx))
		perror("Invalid map\n");
	else
		return (1);
	return (0);
}
