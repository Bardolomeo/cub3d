/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:18:54 by gsapio            #+#    #+#             */
/*   Updated: 2023/07/24 16:20:39 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
int main()
{
	printf("%d\n", ft_isascii(0));
	printf("%d\n", ft_isascii(3));
	printf("%d\n", ft_isascii(';'));
	printf("%d\n", ft_isascii('a'));
	printf("%d\n", ft_isascii(128));
}*/