/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:42:54 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/26 15:10:47 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	if_neg(int *n, int fd)
{
	if (*n < 0)
	{
		*n = -(*n);
		write(fd, "-", 1);
	}
}

static int	ft_exceptions(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (1);
	}
	if (n == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	if (n == 10)
	{
		write(fd, "10", 2);
		return (1);
	}
	return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (ft_exceptions(n, fd))
		return ;
	if (n < 0)
		if_neg(&n, fd);
	if (n > 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	if (n < 10)
	{
		c = n + 48;
		write(fd, &c, 1);
	}
}
