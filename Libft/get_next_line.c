/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:55:33 by gsapio            #+#    #+#             */
/*   Updated: 2023/11/25 15:57:28 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	func_error(int rd, char *back)
{
	if (rd == -1)
	{
		if (back != NULL)
			free (back);
		back = NULL;
		return (0);
	}
	return (1);
}

char	*cut_remainder(char **ret)
{
	char	*temp;
	char	*tmp2;
	int		i;

	i = 0;
	if (!(*ret))
		return (NULL);
	while ((*ret)[i] != '\n' && (*ret)[i] != '\0')
		i++;
	if ((*ret)[i] == 0)
		return (NULL);
	temp = ft_substr(*ret, i + 1, ft_strlen(*ret) - i);
	if (!temp)
		return (NULL);
	temp[ft_strlen(temp)] = 0;
	if ((*ret)[i] == '\n')
	{
		tmp2 = *ret;
		*ret = ft_substr(tmp2, 0, i + 1);
		free (tmp2);
		if (!(*ret))
			return (NULL);
	}
	return (temp);
}

char	*new_line(int fd, char *buf, char *back)
{
	char	*temp;
	int		rd;

	if (!back)
		back = ft_strdup("");
	if (!back)
		return (NULL);
	rd = 1;
	while (rd != 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (!func_error(rd, back))
			return (NULL);
		if (rd == 0)
			break ;
		buf[rd] = 0;
		temp = back;
		back = ft_strjoin(temp, buf);
		if (!back)
			return (NULL);
		free(temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (back);
}

char	*get_next_line(int fd)
{
	static char	*back;
	char		*buf;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	ret = new_line(fd, buf, back);
	free (buf);
	if (!ret)
		back = NULL;
	if (!ret)
		return (NULL);
	back = cut_remainder(&ret);
	if ((back == NULL || *back == 0) && *ret == 0)
	{
		if (back != NULL)
			free (back);
		free (ret);
		back = NULL;
		return (NULL);
	}
	return (ret);
}
