/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:53:55 by clkuznie          #+#    #+#             */
/*   Updated: 2019/12/19 06:53:59 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*
	ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*newlst;
	t_list		*newelem;

	if (!lst || !f || !del || !(newlst = ft_lstnew((*f)(lst->content))))
		return (NULL);
	while ((lst = lst->next))
	{
		if (!(newelem = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, newelem);
	}
	return (newlst);
}
