/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_first_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:38:35 by user42            #+#    #+#             */
/*   Updated: 2021/02/27 18:20:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_operators_as_used(t_lit_status *lit_status)
{
	lit_status->unused_op = 0;
	lit_status->pipe = 0;
	lit_status->redir = 0;
}

static int	is_operator_rep(t_lit_status *lit_status, char *s, int *i)
{
	if (((++(lit_status->unused_op) > 1) && s[*i] != '<' && s[*i] != '>')
		|| ((s[*i] == '<' || s[*i] == '>')
			&& (lit_status->redir)))
		return (1);
	if ((s[*i] == '|' || s[*i] == '<' || s[*i] == '>'))
	{
		lit_status->pipe = (s[*i] == '|');
		if (s[*i] == '<' || s[*i] == '>')
		{
			if (s[*i] == '>')
				*i += (s[*i + 1] == '>');
			lit_status->redir = 1;
		}
	}
	return (0);
}

char		*first_read(char *s)
{
	int				i;
	t_lit_status	lit_status;
	int				non_blank;

	i = -1;
	lit_status_init(&lit_status);
	non_blank = 0;
	while (s[++i])
	{
		if (!ft_isblank(s[i]) && ++non_blank)
		{
			if (is_lit(s[i], &lit_status) || lit_status.dquote
				|| !is_operator(s[i]))
				set_operators_as_used(&lit_status);
			else if (is_operator(s[i]) && is_operator_rep(&lit_status, s, &i))
				return (&(s[i]) + (s[i + 1] = '\0'));
			else if (!is_operator(s[i]))
				set_operators_as_used(&lit_status);
		}
	}
	if (non_blank &&
		(lit_status.quote || lit_status.dquote
		|| lit_status.pipe || lit_status.redir))
		return ("newline");
	return (NULL);
}
