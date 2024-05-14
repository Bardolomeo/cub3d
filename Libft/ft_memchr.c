/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:20:31 by gsapio            #+#    #+#             */
/*   Updated: 2023/11/01 14:57:15 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*data;
	size_t			i;

	ptr = (unsigned char *)s;
	data = (unsigned char *)&c;
	i = 0;
	while (i < n)
	{
		i++;
		if (*ptr == *data)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
/*
int main()
{
	char array[50] = {0, 1, 2, 3, 4, 5};
	int arr[50] = {10, 20, 30, 40, 50, 60, 70};
	printf("%d\n", *(int *)(ft_memchr(arr, 20, 5)));
	printf("%d\n", *(int *)(memchr(arr, 20, 5)));
	printf("%s\n", (char *)(ft_memchr(array, 256 + 2, 3)));
	printf("%s\n", (char *)(memchr(array, 256 + 2, 3)));
}*/
