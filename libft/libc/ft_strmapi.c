/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 07:59:31 by clkuznie          #+#    #+#             */
/*   Updated: 2019/10/21 08:00:33 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*
	ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_s;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = -1;
	if (!(new_s = malloc(sizeof(*s) * ft_strlen(s) + 1)))
		return (NULL);
	while (s[++i])
		new_s[i] = (*f)(i, s[i]);
	new_s[i] = '\0';
	return (new_s);
}
