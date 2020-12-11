/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 00:41:51 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/19 01:39:44 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	*ft_free_lst(t_list *lst, void (*del)(void *))
{
	t_list *store;

	while (lst->next != NULL)
	{
		store = lst;
		lst = lst->next;
		del(store->content);
		free(store);
	}
	del(lst->content);
	free(lst);
	return (NULL);
}

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_elem;
	t_list	*new_lst_start;

	if (lst == NULL)
		return (NULL);
	new_elem = (t_list *)malloc(sizeof(t_list));
	if (new_elem == NULL)
		return (NULL);
	new_lst_start = new_elem;
	while (lst->next != NULL)
	{
		new_elem->content = f(lst->content);
		new_elem->next = (t_list *)malloc(sizeof(t_list));
		new_elem = new_elem->next;
		if (!new_elem)
			return (ft_free_lst(new_lst_start, del));
		lst = lst->next;
	}
	new_elem->content = f(lst->content);
	new_elem->next = NULL;
	return (new_lst_start);
}
