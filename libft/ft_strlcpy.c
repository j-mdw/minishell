/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 21:37:58 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/14 18:50:33 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	i = 0;
	while (i < dstsize)
	{
		if (i == (dstsize - 1) || src[i] == '\0')
		{
			dst[i] = '\0';
			while (src[i] != '\0')
				i++;
			return (i);
		}
		else
			dst[i] = src[i];
		i++;
	}
	while (src[i] != '\0')
		i++;
	return (i);
}
