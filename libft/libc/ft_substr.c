/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 07:51:55 by clkuznie          #+#    #+#             */
/*   Updated: 2019/12/18 08:45:31 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*
	ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	newstr_len;

	if (!s)
		return (NULL);
	newstr_len = ft_strlen(s);
	if (start > newstr_len)
		return ((char *)ft_calloc(1, sizeof(*s)));
	newstr_len = (newstr_len - start < len) ? newstr_len - start : len;
	if (!(newstr = malloc(sizeof(*s) * newstr_len + 1)))
		return (NULL);
	ft_memmove(newstr, s + start, newstr_len);
	newstr[newstr_len] = '\0';
	return (newstr);
}
