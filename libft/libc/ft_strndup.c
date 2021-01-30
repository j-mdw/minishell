/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 05:34:51 by clkuznie          #+#    #+#             */
/*   Updated: 2019/11/24 05:34:55 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*
	ft_strndup(char const *s1, size_t n)
{
	size_t	src_len;
	char	*s2;

	src_len = ft_strlen(s1);
	if (src_len <= n)
		s2 = ft_strdup(s1);
	else
	{
		if (!(s2 = malloc(sizeof(*s1) * n + 1)))
			return (NULL);
		ft_memmove(s2, s1, n);
		s2[n] = '\0';
	}
	return (s2);
}
