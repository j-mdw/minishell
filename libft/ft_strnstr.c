/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:17:58 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/14 18:50:56 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t len_needle;

	i = 0;
	len_needle = 0;
	while (needle[len_needle] != '\0')
		len_needle++;
	if (len_needle == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i] == needle[j] && i < len && haystack[i] != '\0')
		{
			i++;
			j++;
		}
		if (j == len_needle)
			return (&((char *)haystack)[i - j]);
		i = i + 1 - j;
	}
	return (NULL);
}
