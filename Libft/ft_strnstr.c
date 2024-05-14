/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:17:54 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/22 15:07:14 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b;
	size_t	i;
	size_t	j;

	i = -1;
	if (*little == 0)
		return ((char *)big);
	while (++i < len && big[i] != 0)
	{
		j = 0;
		if (big[i] == little[j])
		{
			b = (char *)&big[i];
			while (big[i] == little[j] && i < len && big[i++] != 0)
			{
				if (little[++j] == '\0')
					return (b);
			}
			i -= j;
		}
		b = NULL;
	}
	if (len == 0 || *big == 0)
		return (NULL);
	return (b);
}
/*
int main()
{
	char haystack[30] = "aaabcabcd";
	char needle[10] = "aabc";

	printf("%s\n", ft_strnstr(haystack, needle, -1));
	//printf("%s\n", strnstr("lama donna", "ma do", -1));
	printf("%s\n", ft_strnstr("lama donna", "", 10));
	//printf("%s\n", strnstr("lama donna", "", 10));
	printf("%s\n", ft_strnstr("lama donna", "ma do", 3));
	//printf("%s\n", strnstr("lama donna", "ma do", 3));
	printf("%s\n", ft_strnstr("", "lama", 4));
	//printf("%s\n", strnstr("", "lama", 4));
}
*/
