/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:39:57 by gsapio            #+#    #+#             */
/*   Updated: 2024/06/19 14:54:13 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_all_elements(t_mlx *mlx)
{
	int	i;

	i = 0;
	if (mlx->ceiling_color == -1 || mlx->floor_color == -1)
	{
		destroy_game_on_start(mlx);
		return (0);
	}
	while (i < 4)
	{
		if (mlx->images[i].img_ptr == NULL)
		{
			destroy_game_on_start(mlx);
			return (0);
		}
		i++;
	}
	return (1);
}

void	set_color(char *str, int *color)
{
	int		i;
	char	**rgb_s;
	char	*str_color;

	i = skip_spaces(str);
	str_color = ft_strtrim(str + i, "\n");
	rgb_s = ft_split(str_color, ',');
	i = 0;
	while (rgb_s[i])
		i++;
	if (i < 3)
	{
		ft_free_matrix((void **)rgb_s);
		free(str_color);
		return ;
	}
	*color = create_trgb(0, (unsigned char)ft_atoi(rgb_s[0]),
			(unsigned char)ft_atoi(rgb_s[1]), (unsigned char)ft_atoi(rgb_s[2]));
	ft_free_matrix((void **)rgb_s);
	free(str_color);
}

void	set_image(char *str, t_image *image, t_mlx *mlx)
{
	int		i;
	char	*filename;

	i = skip_spaces(str);
	filename = ft_strtrim(str + i, "\n");
	image->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, filename,
			&image->i_width, &image->i_height);
	free(filename);
}

int	get_elements(char *str, t_mlx *mlx)
{
	int	i;

	i = skip_spaces(str);
	if (get_positioning(i, mlx, str))
		return (1);
	else if (ft_strncmp(str + i, "F ", 2) == 0 && mlx->keys.f == 0)
	{
		set_color(str + i + 2, &mlx->floor_color);
		mlx->keys.f = 1;
	}
	else if (ft_strncmp(str + i, "C ", 2) == 0 && mlx->keys.c == 0)
	{
		set_color(str + i + 2, &mlx->ceiling_color);
		mlx->keys.c = 1;
	}
	else if (*(str + i) == '\n' || *(str + i) == '1')
		return (1);
	else
	{
		free(str);
		destroy_game_on_start(mlx);
		return (0);
	}
	return (1);
}

int	check_elements(int fd, char **argv, t_mlx *mlx)
{
	char *temp;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (0);
	temp = get_next_line(fd);
	if (!temp)
		error_fclose(&fd);
	while (temp != NULL)
	{
		if (!get_elements(temp, mlx))
		{
			error_fclose(&fd);
			return (0);
		}
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
	if (!check_all_elements(mlx))
		return (0);
	return (1);
}