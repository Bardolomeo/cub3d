/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:51:14 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/26 16:10:25 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_string_to_int(int *nb, size_t *i, size_t *len, const char *nptr)
{
	int		prov;
	size_t	j;

	while (*len > 0)
	{
		j = 0;
		prov = nptr[*i] - 48;
		while (j < (*len - 1))
		{
			prov *= 10;
			j++;
		}
		*nb += prov;
		(*len)--;
		(*i)++;
	}
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		nb;
	size_t	len;

	i = 0;
	sign = 1;
	len = 0;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		i++;
		len++;
	}
	i -= len;
	ft_string_to_int(&nb, &i, &len, nptr);
	return (nb * sign);
}
/*
int main()
{
	printf("%d", ft_atoi("   2147483647"));
}
*/
