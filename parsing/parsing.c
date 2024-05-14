/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:41:48 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/14 17:39:02 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <fcntl.h>
#include <stdio.h>

// int	check_map(int fd, char **argv, t_mlx *mlx)
// {
// }


void	free_images(t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (mlx->images[i].img_ptr)
		{
			mlx_destroy_image(mlx->mlx_ptr, mlx->images[i].img_ptr);
			free(mlx->images[i].img_ptr);
		}
}

int	check_all_elements(t_mlx *mlx)
{
	int	i;

	i = 0;
	if (mlx->ceiling_color == 0 || mlx->floor_color == 0)
	{
		free_images(mlx);
		return (0);
	}
	while (i < 4)
	{
		if (mlx->images[i].img_ptr == NULL)
		{
			free_images(mlx);
			return (0);
		}
		i++;
	}
	return (1);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

void	set_color(char *str, int *color, t_mlx *mlx)
{
	int		i;
	char	**rgb_s;
	char	*str_color;

	i = skip_spaces(str);
	str_color = ft_strtrim(str + i, "\n");
	rgb_s = ft_split(str_color, ',');
	*color = create_trgb(0, ft_atoi(rgb_s[0]), ft_atoi(rgb_s[1]),
			ft_atoi(rgb_s[2]));
}

void	set_image(char *str, t_image image, t_mlx *mlx)
{
	int		i;
	char	*filename;

	i = skip_spaces(str);
	filename = ft_strtrim(str + i, "\n");
	image.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, filename,
			&image.i_width, &image.i_height);
}

int	get_texture(char *str, t_mlx *mlx)
{
	int	i;

	i = skip_spaces(str);
	if (ft_strncmp(str + i, "NO ", 3) == 0)
		set_image(str + i + 3, mlx->images[NO], mlx);
	else if (ft_strncmp(str + i, "SO ", 3) == 0)
		set_image(str + i + 3, mlx->images[SO], mlx);
	else if (ft_strncmp(str + i, "WE ", 3) == 0)
		set_image(str + i + 3, mlx->images[WE], mlx);
	else if (ft_strncmp(str + i, "EA ", 3) == 0)
		set_image(str + i + 3, mlx->images[EA], mlx);
	else if (ft_strncmp(str + i, "F ", 2) == 0)
		set_color(str + i + 2, &mlx->floor_color, mlx);
	else if (ft_strncmp(str + i, "C ", 2) == 0)
		set_color(str + i + 2, &mlx->ceiling_color, mlx);
	else if (*(str + i) == '\n' || *(str + i) == '1')
		return (1);
	else
	{
		free(str);
		free_images(mlx);
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
	// else if (!check_map(fd, argv, mlx))
	// 	perror("Invalid map\n");
	else
		return (1);
	return (0);
}
