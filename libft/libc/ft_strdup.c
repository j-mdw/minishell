/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:56:04 by clkuznie          #+#    #+#             */
/*   Updated: 2019/10/15 11:22:00 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*
	ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;

	i = ft_strlen(s1);
	if (!(s2 = malloc(sizeof(*s1) * i + 1)))
		return (NULL);
	ft_memmove(s2, s1, i);
	s2[i] = '\0';
	return (s2);
}
