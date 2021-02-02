/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 07:58:02 by clkuznie          #+#    #+#             */
/*   Updated: 2021/02/02 11:30:45 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_strs(char const *s, char c)
{
	int		i;
	int		s_nbr;

	i = 0;
	s_nbr = 0;
	if (!c)
		return ((s[i]) ? s_nbr + 1 : s_nbr);
	while (s[i])
	{
		if (s[i] != c)
		{
			++s_nbr;
			while (s[i] && s[i] != c)
				++i;
			continue ;
		}
		++i;
	}
	return (s_nbr);
}

static void	clean_mem(char ***strs)
{
	int		i;

	i = 0;
	while ((*strs)[i])
	{
		free((*strs)[i]);
		++i;
	}
	free(*strs);
	*strs = NULL;
}

static int	duplicate(char const *s, char c, char **strs, int s_nbr)
{
	int		i;
	int		j;

	i = 0;
	while (i < s_nbr)
	{
		j = 0;
		while (s[j] == c)
			++j;
		s += j;
		j = 0;
		while (s[j] && s[j] != c)
			++j;
		if (!(strs[i] = ft_strndup(s, j)))
			return (0);
		s += j;
		++i;
	}
	return (1);
}

char		**
	ft_split(char const *s, char c)
{
	char	**strs;
	int		s_nbr;

	if (s)
		s_nbr = count_strs(s, c);
	else
		return (NULL);
	if (!(strs = malloc((s_nbr + 1) * sizeof(s))))
		return (NULL);
	strs[s_nbr] = NULL;
	if (!duplicate(s, c, strs, s_nbr))
		clean_mem(&strs);
	return (strs);
}
