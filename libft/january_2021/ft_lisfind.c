/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lisfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:23:11 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 12:23:13 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list
	*ft_lstfind(t_list *begin, void *content)
{
	while (begin)
	{
		if (!(ft_strcmp(begin->content, content)))
			return (begin);
		begin = begin->next;
	}
	return (NULL);
}
