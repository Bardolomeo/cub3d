/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:18:54 by gsapio            #+#    #+#             */
/*   Updated: 2023/07/24 16:20:39 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*pt;

	if (dest == NULL && src == NULL)
		return (dest);
	ptr = (unsigned char *)dest;
	pt = (unsigned char *)src;
	while (n--)
	{
		*ptr = *pt;
		ptr++;
		pt++;
	}
	return (dest);
}
/*
int main()
{
	char src[20] = "12345678";
	char dest[20] = "abcdefghijklmno";

	ft_memcpy(dest, src, 5);
	printf("%s\n", dest);
	ft_memcpy(dest, src, 0);
	printf("%s\n", dest);
	ft_memcpy(dest, src, 8);
	printf("%s\n", dest);
	ft_memcpy(dest, src, 9);
	printf("%s\n", dest);
}
*/
