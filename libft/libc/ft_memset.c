/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:15:16 by clkuznie          #+#    #+#             */
/*   Updated: 2019/10/15 07:00:42 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*
	ft_memset(void *b, int c, size_t len)
{
	while (len != 0)
		((unsigned char *)b)[--len] = (unsigned char)c;
	return (b);
}
