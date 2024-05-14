/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:33:35 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/21 14:52:11 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}
/*
int main()
{
	printf("%d\n", ft_toupper('c'));
	printf("%d\n", ft_toupper('A'));
	printf("%d\n", ft_toupper('.'));
	printf("%d\n", ft_toupper('b'));
	printf("%d\n", ft_toupper(4.7));
}*/
