/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 00:39:22 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/19 00:39:48 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *store;

	if (lst != NULL)
	{
		if (*lst == NULL)
			free(*lst);
		else
		{
			while ((*lst)->next != NULL)
			{
				store = *lst;
				*lst = (*lst)->next;
				del(store->content);
				free(store);
			}
			del((*lst)->content);
			free(*lst);
		}
		*lst = NULL;
	}
}
