/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:18:54 by gsapio            #+#    #+#             */
/*   Updated: 2023/07/24 16:20:39 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n--)
		*ptr++ = (unsigned char) c;
	return (s);
}
/*
int main()
{
	char str[50] = "ciaocane";
	ft_memset(str, 'a', 4);
	printf("%s\n", str);
	ft_memset(str, 'd', 0);
	printf("%s\n", str);
}*/
