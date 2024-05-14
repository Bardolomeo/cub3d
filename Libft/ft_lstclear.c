/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:52:56 by gsapio            #+#    #+#             */
/*   Updated: 2023/11/01 14:41:20 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst)
	{
		if (!*lst)
			lst = NULL;
		else
		{
			while (*lst)
			{
				temp = (*lst)->next;
				ft_lstdelone(*lst, del);
				*lst = temp;
			}
		}
	}
}
