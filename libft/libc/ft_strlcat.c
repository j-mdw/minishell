/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:50:11 by clkuznie          #+#    #+#             */
/*   Updated: 2019/10/16 21:37:40 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t
	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = (!dst ? 0 : ft_strlen(dst));
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	if (dst_len + src_len < dstsize)
		ft_memmove(dst + dst_len, src, src_len + 1);
	else
	{
		ft_memmove(dst + dst_len, src, dstsize - dst_len - 1);
		*(dst + dstsize - 1) = '\0';
	}
	return (dst_len + src_len);
}
