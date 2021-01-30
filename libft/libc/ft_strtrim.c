/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 07:56:36 by clkuznie          #+#    #+#             */
/*   Updated: 2019/10/21 07:57:23 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_start(char const *s1, char const *set)
{
	int		i;

	i = 0;
	while (s1[i] && ft_isinset(s1[i], set))
		++i;
	return (i);
}

static int	find_end(char const *s1, char const *set)
{
	int		i;

	i = (int)ft_strlen(s1) - 1;
	while (i >= 0 && ft_isinset(s1[i], set))
		--i;
	return (i);
}

char		*
	ft_strtrim(char const *s1, char const *set)
{
	int		trimmed_len;

	if (!s1 || !set)
		return (NULL);
	if ((trimmed_len = find_end(s1, set) - find_start(s1, set)) < 0)
		return (ft_strndup(s1, 0));
	return (ft_strndup(s1 + find_start(s1, set), trimmed_len + 1));
}
