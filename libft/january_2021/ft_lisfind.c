/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lisfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:23:11 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 21:31:57 by user42           ###   ########.fr       */
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
