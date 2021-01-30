/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:28:23 by clkuznie          #+#    #+#             */
/*   Updated: 2019/10/14 10:49:06 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*
	ft_memcpy(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return (dst);
	while (n && dst != src)
	{
		--n;
		((char *)dst)[n] = ((char *)src)[n];
	}
	return (dst);
}
