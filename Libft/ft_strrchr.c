/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:57:39 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/22 14:21:45 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;
	char	*c2;

	ptr = (char *)s;
	c2 = (char *)&c;
	i = ft_strlen(ptr) + 1;
	while (--i >= 0)
		if (ptr[i] == *c2)
			return (&ptr[i]);
	return (NULL);
}
/*
int main()
{
	char str[50] = "ciau suca";
	char s[] = "tripouille";cd 
	printf("%s\n", ft_strrchr(s, 't'));
	printf("%s\n", ft_strrchr("zio pera", 'u'));
	printf("%s\n", ft_strrchr("uuuuuu", 'u'));
	printf("%s\n", ft_strrchr("", '\0'));
}
*/
