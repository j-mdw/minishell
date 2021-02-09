/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:27:53 by clkuznie          #+#    #+#             */
/*   Updated: 2021/01/29 16:27:54 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_lit(char c, t_lit_status *lit_status)
{
	if (!lit_status->quote && !lit_status->dquote && !lit_status->backs)
	{
		lit_status->quote = (c == '\'');
		lit_status->dquote = (c == '\"');
		lit_status->backs = (c == '\\');
		return (0);
	}
	lit_status->quote -= ((c == '\'') && lit_status->quote);
	lit_status->dquote -= ((c == '\"') && lit_status->dquote);
	lit_status->backs = 0;
	return (1);
}

static int	count_strs(char const *s, char c, t_lit_status *lit_status)
{
	int				i;
	int				s_nbr;

	i = 0;
	s_nbr = 0;
	if (!c)
		return ((s[i]) ? s_nbr + 1 : s_nbr);
	while (s[i])
	{
		if (is_lit(s[i], lit_status) || s[i] != c)
		{
			++s_nbr;
			++i;
			while (s[i] && (is_lit(s[i], lit_status) || s[i] != c))
				++i;
			continue ;
		}
		++i;
	}
	return (s_nbr);
}

static void	clean_mem(char ***strs)
{
	int				i;

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
	int				i;
	int				j;
	t_lit_status	lit_status;

	lit_status.quote = 0;
	lit_status.dquote = 0;
	lit_status.backs = 0;
	i = 0;
	while (i < s_nbr)
	{
		j = 0;
		while (!is_lit(s[j], &lit_status) && s[j] == c)
			++j;
		s += j;
		j = 1;
		while (s[j] && (is_lit(s[j], &lit_status) || s[j] != c))
			++j;
		if (!(strs[i] = ft_strndup(s, j)))
			return (0);
		s += j;
		++i;
	}
	return (1);
}

char		**
	shell_split(char const *s, char c)
{
	char			**strs;
	int				s_nbr;
	t_lit_status	lit_status;

	lit_status.quote = 0;
	lit_status.dquote = 0;
	lit_status.backs = 0;
	if (s)
		s_nbr = count_strs(s, c, &lit_status);
	if (!(strs = malloc((s_nbr + 1) * sizeof(s))))
		return (NULL);
	strs[s_nbr] = NULL;
	if (!duplicate(s, c, strs, s_nbr))
		clean_mem(&strs);
	return (strs);
}
