/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:44:23 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/31 20:42:29 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_ind_trim(int *start, int *end, const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(set))
	{
		while (s1[*start] == set[i] && *start < *end)
		{
			(*start)++;
			i = 0;
		}
		i++;
	}
	i = 0;
	while (i < (int)ft_strlen(set))
	{
		while (s1[*end] == set[i] && *end > *start)
		{
			(*end)--;
			i = 0;
		}
		i++;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1) - 1;
	ft_ind_trim(&start, &end, s1, set);
	if (start == end && s1[start + 1] == 0)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}
/*
int main(void)
{
	printf("%s \n", ft_strtrim("abcdba", "acb"));

	printf("%s\n", ft_strtrim(" ammazza ", " a"));
	printf("%s\n", ft_strtrim(" ammazza ", " amz"));
	//printf("%s\n", ft_strtrim(ptr, " a"));
	//printf("%s\n", ft_strtrim(" ammazza ", ptr));
	printf("%s\n", ft_strtrim("", ""));
}
*/
