/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:58:32 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/26 13:57:13 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_exception(int n)
{
	char	*str;

	if (n == 0)
	{
		str = ft_calloc(2, sizeof(char));
		if (!str)
			return (NULL);
		str[0] = 48;
		str[1] = 0;
		return (str);
	}
	return (NULL);
}

static int	ft_sign_and_count(int n, int *sign, long int *nb)
{
	int			len;
	long int	numb;

	len = 0;
	numb = n;
	if (numb < 0)
	{
		*sign = -1;
		numb = -numb;
		len++;
	}
	*nb = numb;
	while (numb > 0)
	{
		numb /= 10;
		len++;
	}
	return (len);
}

static void	ft_invert(char	*str)
{
	size_t	i;
	size_t	j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < ft_strlen(str) / 2)
	{
		tmp = str[i];
		str[i++] = str[j];
		str[j--] = tmp;
	}
	str[ft_strlen(str)] = 0;
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			sign;
	int			len;
	char		*ret;
	int			i;

	sign = 1;
	len = ft_sign_and_count(n, &sign, &nb);
	if (n == 0)
		return (ft_exception(n));
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	while (nb > 0)
	{
		ret[++i] = (nb % 10) + 48;
		nb /= 10;
	}
	if (sign == -1)
		ret[++i] = '-';
	ft_invert(ret);
	return (ret);
}
/*
int main()
{
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(-1234));
}
*/
