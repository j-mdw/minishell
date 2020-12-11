/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 00:40:38 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/19 00:41:01 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *ptr;

	if (lst != NULL)
	{
		ptr = lst;
		while (ptr->next != NULL)
		{
			f(ptr->content);
			ptr = ptr->next;
		}
		f(ptr->content);
	}
}
