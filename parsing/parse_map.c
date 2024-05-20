/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:26:41 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/20 18:37:28 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	set_cursor_map(int *fd, char **tmp_str)
{
	int	i;

	*tmp_str = get_next_line(*fd);
	if (!(*tmp_str))
		return (0);
	while (*tmp_str)
	{
		i = skip_spaces(*tmp_str);
		if ((*tmp_str)[i] == '1')
			break ;
		free(*tmp_str);
		*tmp_str = get_next_line(*fd);
		if (!(*tmp_str))
			return (0);
	}
	return (1);
}

int	count_map_lines(int *fd)
{
	char	*tstr;
	int		count;

	tstr = NULL;
	if (!set_cursor_map(fd, &tstr))
		return (0);
	count = 1;
	free(tstr);
	tstr = get_next_line(*fd);
	if (!tstr)
		return (0);
	while (tstr)
	{
		free(tstr);
		tstr = get_next_line(*fd);
		count++;
	}
	return (count);
}

int	initialize_map(char ***map, int *fd)
{
	char	*str;
	char	*tstr;
	int		i;

	i = 0;
	set_cursor_map(fd, &tstr);
	str = ft_strtrim(tstr, "\n");
	(*map)[i++] = str;
	free(tstr);
	while (*str)
	{
		tstr = get_next_line(*fd);
		str = ft_strtrim(tstr, "\n");
		free(tstr);
		if (!*str)
		{
			free(str);
			break ;
		}
		(*map)[i] = str;
		i++;
	}
	return (1);
}

/*per il check della mappa alla fine controllo che:
	- ci sia un solo player
	- se trova il player o uno zero questi devono essere circondati da altri zeri,
		uni o dal player.
	- Se trova uno zero o il player nei bordi della mappa esce direttamente*/
int	check_map(char **map, t_mlx *mlx)
{
	int		i;
	int		j;
	char	player;

	player = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == '0' || valid_player(map[i][j]))
			{
				if (i == 0 || map[i] == NULL || j == 0 || !valid_tile(map, i,
						j))
					return (destroy_game_on_start(mlx));
				if (valid_player(map[i][j]))
					player += map[i][j];
			}
	}
    if (!valid_player(player))
    {
        return (destroy_game_on_start(mlx));
    }
    return (1);
}


int	map_manager(int fd, char **argv, t_mlx *mlx)
{
	char **tmp_map;
	int cnt_lines;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (destroy_game_on_start(mlx));
	cnt_lines = count_map_lines(&fd);
	if (!cnt_lines || cnt_lines == 1)
		return (destroy_game_on_start(mlx));
	close(fd);
	tmp_map = malloc(sizeof(char *) * (cnt_lines + 1));
	tmp_map[cnt_lines] = NULL;
	fd = open(argv[1], O_RDONLY);
	if (!initialize_map(&tmp_map, &fd))
		return (destroy_game_on_start(mlx));
	close(fd);
	if (!check_map(tmp_map, mlx))
	{
		ft_free_matrix((void **)tmp_map);
		return (0);
	}
	mlx->map = tmp_map;
	return (1);
}