/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:51:30 by clkuznie          #+#    #+#             */
/*   Updated: 2019/10/16 20:50:02 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*
	ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	int		i;

	i = 0;
	if (*needle != '\0')
	{
		needle_len = ft_strlen(needle);
		while (1)
		{
			if (needle_len > len && haystack)
				return (NULL);
			if (haystack[i] != *needle && ++i && len--)
				continue ;
			if (ft_strncmp(haystack + i, needle, needle_len) == 0)
				break ;
			++i;
			--len;
		}
	}
	return ((char *)&haystack[i]);
}
