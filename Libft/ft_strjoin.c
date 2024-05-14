/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:25:46 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/28 13:05:01 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*res;

	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	if ((len) == 0)
		res = (char *)malloc(sizeof(char) * 1);
	else
		res = (char *)malloc(sizeof(char) * (len) + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (++i < len && s1[j] != 0)
		res[i] = s1[j++];
	j = 0;
	while (i < len && s2[j] != 0)
		res[i++] = s2[j++];
	res[i] = 0;
	return (res);
}
/*
int main(void)
{
	printf("%s\n", ft_strjoin("cacca ", "pupu"));
	printf("%s\n", ft_strjoin("", ""));
	return (0);
}
*/
