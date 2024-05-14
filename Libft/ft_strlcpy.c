/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:45:25 by gsapio            #+#    #+#             */
/*   Updated: 2023/11/01 14:57:43 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = -1;
	if (size == 0)
	{
		++i;
		while (src[i])
			i++;
		return (i);
	}
	while (++i < size - 1 && src[i] != '\0')
		dst[i] = src[i];
	if (i < size)
		dst[i] = 0;
	while (src[i])
		i++;
	return (i);
}
/*
int main()
{
	char dest[] = "123456";
	char dest1[] = "123456";

	printf("%d\t%s\n", (int)ft_strlcpy(dest, "abc", 0), dest);
	printf("%d\t%s\n", (int)ft_strlcpy(dest, "abc", 3), dest);
	printf("%d\t%s\n", (int)ft_strlcpy(dest, "abc", 5), dest);
	printf("%d\t%s\n", (int)ft_strlcpy(dest, "", 5), dest);
	printf("%d\t%s\n", (int)strlcpy(dest1, "abc", 0), dest1);
	printf("%d\t%s\n", (int)strlcpy(dest1, "abc", 3), dest1);
	printf("%d\t%s\n", (int)strlcpy(dest1, "abc", 5), dest1);
	printf("%d\t%s\n", (int)strlcpy(dest, "", 5), dest);
	printf("%d\n", (int)strlcpy("", "abc", 3));
	printf("%d\n", (int)strlcpy("", "abc", 3));
}*/
