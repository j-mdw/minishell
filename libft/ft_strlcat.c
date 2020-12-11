/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 21:41:51 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/14 18:50:16 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;

	i = ft_strlen(dst);
	j = 0;
	if (i >= dstsize)
		return (dstsize + ft_strlen(src));
	while ((i + j) < dstsize)
	{
		if ((i + j) != (dstsize - 1) && src[j] != '\0')
		{
			dst[i + j] = src[j];
			j++;
		}
		else
		{
			dst[i + j] = '\0';
			i = dstsize;
		}
	}
	return (ft_strlen(dst) + (ft_strlen(src) - j));
}
