/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 05:36:23 by clkuznie          #+#    #+#             */
/*   Updated: 2019/12/19 05:36:24 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*
	ft_lstnew(void *content)
{
	t_list		*newelem;

	if (!(newelem = malloc(sizeof(t_list))))
		return (NULL);
	newelem->content = content;
	newelem->next = NULL;
	return (newelem);
}
