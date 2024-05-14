/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:02:28 by gsapio            #+#    #+#             */
/*   Updated: 2023/11/01 15:35:21 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb != 0 && size > ULONG_MAX / nmemb)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
/*
int main()
{
 	void *str = ft_calloc(0, 0);
	void *str2 = calloc(0, 0);


 	if (str == ((void*)0))
		printf("suca\n");
	if (str2 != ((void*)0))
		printf("noi");
}
*/
