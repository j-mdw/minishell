/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 07:55:32 by clkuznie          #+#    #+#             */
/*   Updated: 2019/10/21 07:57:37 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*
	ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*newstr;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	if (!(newstr = malloc(sizeof(*s1) * total_len + 1)))
		return (NULL);
	ft_memmove(newstr, s1, ft_strlen(s1) + 1);
	ft_strlcat(newstr, s2, total_len + 1);
	return (newstr);
}
