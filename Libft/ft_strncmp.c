/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:18:27 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/22 15:15:51 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned long	i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*str1 == *str2 && *str1 != 0 && i < n - 1)
	{
		str1++;
		str2++;
		i++;
	}
	if ((*str1 - *str2) < 0)
		return (-1);
	else if ((*str1 - *str2) > 0)
		return (1);
	else
		return (0);
}

/*
int main()
{
	printf("%d\n", ft_strncmp("t", "", 0));
	printf("%d\n", ft_strncmp("", "1", 1));
	printf("%d\n", ft_strncmp("1", "", 1));
	printf("%d\n", ft_strncmp("cappa", "abbaio", 4));
	printf("%d\n\n", ft_strncmp("......", "......", 7));
	printf("%d\n", strncmp("t", "", 0));
	printf("%d\n", strncmp("", "1", 1));
	printf("%d\n", strncmp("1", "", 1));
	printf("%d\n", strncmp("cappa", "abbaio", 4));
	printf("%d\n\n", strncmp("......", "......", 7));
}
*/
