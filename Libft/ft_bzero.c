/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:18:54 by gsapio            #+#    #+#             */
/*   Updated: 2023/07/24 16:20:39 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = 0;
}
/*
int main()
{
	char str[50] = "mannaggia mannaggia";
	ft_bzero(str, 7);
	printf("%s\n", &str[7]);
	ft_bzero(str, 0);
	printf("%s\n", &str[7]);
	ft_bzero(str, 30);
	printf("%s\n", &str[37]);
}*/
