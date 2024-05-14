/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:37:16 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/22 14:15:30 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	int		i;
	char	*c2;

	i = 0;
	ptr = (char *)s;
	c2 = (char *)&c;
	while (ptr[i] != *c2 && ptr[i] != 0)
		i++;
	if (ptr[i] == *c2)
		return (&ptr[i]);
	return (NULL);
}
/*
int main()
{
	char str[50] = "ciau suca";
	printf("%s\n", ft_strchr(str, 'u'));
	printf("%s\n", ft_strchr("zio pera", 'u'));
	printf("%s\n", ft_strchr("uuuuuu", 'u'));
	printf("%s\n", ft_strchr("", '\0'));
}*/
