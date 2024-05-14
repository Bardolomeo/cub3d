/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:14:19 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/31 20:12:23 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_stralloc(char	*scpy, char	**strs, char c)
{
	int		i;
	int		j;
	size_t	cnt_char;

	i = 0;
	j = -1;
	cnt_char = 0;
	while (scpy[i] != 0)
	{
		cnt_char = 0;
		while (scpy[i] == c)
			i++;
		while (scpy[i] != 0 && scpy[i++] != c)
			(cnt_char)++;
		if (!(scpy[i] == 0 && scpy[i - 1] == c && scpy[i - 2] == c))
			strs[++j] = (char *)ft_calloc((cnt_char) + 1, sizeof(char));
		if (!strs[j])
		{
			while (j >= 0)
				free(strs[j--]);
			free(strs);
			return (0);
		}
	}
	return (1);
}

static void	ft_count_words(char	*scpy, size_t	*cnt, char c)
{
	while (*scpy)
	{
		while (*scpy == c)
			scpy++;
		if (*scpy != 0)
			(*cnt)++;
		while (*scpy != c && *scpy != 0)
			scpy++;
	}
}

static int	ft_word_ini(char	*scpy, char	**strs, char c, size_t cnt)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (!ft_stralloc(scpy, strs, c))
		return (0);
	j = 0;
	while (scpy[j] && i < cnt)
	{
		k = 0;
		while (scpy[j] == c && scpy[j] != 0)
			j++;
		while (scpy[j] != c && scpy[j] != 0)
		{
			strs[i][k] = scpy[j];
			k++;
			j++;
		}
		strs[i][k] = 0;
		i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	char	*scpy;
	size_t	cnt;

	if (s == NULL)
		return (NULL);
	scpy = (char *)s;
	cnt = 0;
	ft_count_words(scpy, &cnt, c);
	if (cnt == 0)
	{
		strs = (char **)ft_calloc(1, sizeof(char *));
		if (!strs)
			return (NULL);
		strs[0] = NULL;
		return (strs);
	}
	strs = (char **)ft_calloc((cnt + 1), sizeof(char *));
	if (strs == NULL)
		return (NULL);
	if (!ft_word_ini(scpy, strs, c, cnt))
		return (NULL);
	strs[cnt] = NULL;
	return (strs);
}
/*
int main()
{
	char **strs = ft_split("split  ||this|for|me|||||!|", '|');
	int i = 0;

	while (strs[i])
	{
		printf("%s\n", strs[i]);
		free(strs[i]);
		i++;
	}
	free(strs);
	i++;
}
*/
