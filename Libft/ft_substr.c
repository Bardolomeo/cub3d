/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:05:53 by gsapio            #+#    #+#             */
/*   Updated: 2023/11/18 19:11:40 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_allocstr(int *copy_len, size_t len)
{
	char	*copy;

	if (len >= (size_t)(*copy_len) && *copy_len > 0)
		copy = (char *)malloc(sizeof(*copy) * (*copy_len) + 1);
	else
		copy = (char *)malloc(sizeof(*copy) * len + 1);
	if (!copy)
		return (NULL);
	return (copy);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*copy;
	int		i;
	int		copy_len;

	copy_len = ft_strlen(s) - start;
	copy = ft_allocstr(&copy_len, len);
	if (!copy)
		return (NULL);
	if (start >= (int)ft_strlen(s))
	{
		free (copy);
		copy = (char *)malloc(sizeof(*copy) * 1);
		if (!copy)
			return (NULL);
		*copy = 0;
		return (copy);
	}
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < len && s[i + start] != 0)
		copy[i] = s[i + start];
	copy[i] = 0;
	return (copy);
}
/*
int main()
{
	char str[] = "123456";
	printf("%s\n", ft_substr(str, 100, 1));
}
*/
