/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:32:12 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/22 14:38:59 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	i = ft_strlen(src);
	j = ft_strlen(dst);
	if (size == 0)
		return (i);
	if (size < j && (int)size > 0)
		i += size;
	else
		i += j;
	while (src[k] && (k + j) < size - 1)
	{
		dst[j + k] = src[k];
		k++;
	}
	dst[j + k] = 0;
	return (i);
}
/*
int main()
{
	char dest[50] = "123456";
	char dest1[50] = "123456";

	printf("%d\t%s\n", (int)ft_strlcat(dest, "abc", -1), dest);
	printf("%d\t%s\n", (int)ft_strlcat(dest, "abc", 10), dest);
	printf("%d\t%s\n", (int)ft_strlcat(dest, "abc", 4), dest);
	printf("%d\t%s\n\n", (int)ft_strlcat(dest, "", 5), dest);
	printf("%d\t%s\n\n", (int)ft_strlcat(dest, "fddsfdfgfd", 12), dest);
	printf("%d\t%s\n", (int)strlcat(dest1, "abc", -1), dest1);
	printf("%d\t%s\n", (int)strlcat(dest1, "abc", 10), dest1);
	printf("%d\t%s\n", (int)strlcat(dest1, "abc", 4), dest1);
	printf("%d\t%s\n", (int)strlcat(dest, "", 5), dest1);
	printf("%d\t%s\n\n", (int)strlcat(dest1, "fddsfdfgfd", 12), dest1);
	printf("%d\n", (int)ft_strlcat("", "a", 3));
	printf("%d\n", (int)strlcat("", "a", 3));
}
*/
