/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:16:25 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/31 19:29:54 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*str;

	len = ft_strlen(s);
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s[++i])
		str[i] = s[i];
	str[i] = 0;
	return (str);
}
/*
int main()
{
	printf("%s", ft_strdup("qwertyuiopasdfghjkwrghrysjharthtehthrehthth"));
}*/
