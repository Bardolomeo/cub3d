/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:26:18 by gsapio            #+#    #+#             */
/*   Updated: 2023/10/26 16:42:22 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (lst)
	{
		if (!(*lst))
		{
			*lst = new;
		}
		else
		{
			ptr = ft_lstlast(*(lst));
			ptr->next = new;
		}
	}
}
