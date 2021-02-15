/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:38:35 by user42            #+#    #+#             */
/*   Updated: 2021/02/15 16:42:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#include <string.h>

typedef struct	s_lit_status {
		int				quote;
		int				dquote;
		int				backs;
		int				unused_op;
		int				pipe;
		int				redir;
}				t_lit_status;


int
	ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int			is_lit(char c, t_lit_status *lit_status)
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

void		lit_status_init(t_lit_status *lit_status)
{
	lit_status->quote = 0;
	lit_status->dquote = 0;
	lit_status->backs = 0;
	lit_status->unused_op = 1;
	lit_status->pipe = 0;
	lit_status->redir = 0;
}

static int	is_operator(char c)
{
	return (c == '|' || c == ';' || c == '<' || c == '>');
}

static void	set_operators_as_used(t_lit_status *lit_status)
{
	lit_status->unused_op = 0;
	lit_status->pipe = 0;
	lit_status->redir = 0;
}

static int	is_operator_repeted(t_lit_status *lit_status, char *s, int *i)
{
	if ((++(lit_status->unused_op) > 1))
		return (1);
	if ((s[*i] == '|' || s[*i] == '<' || s[*i] == '>'))
	{
		lit_status->pipe = s[*i]== '|';
		if (s[*i] == '<' || (s[*i] == '>' && (*i += (s[*i + 1] == '>'))))
			lit_status->redir = 1;
	}
	return (0);
}

char		*first_read(char *s)
{
	int				i;
	t_lit_status	lit_status;
	int				non_blank;

	i = -1;
	non_blank = 0;
	while (s[++i])
	{
		if (!ft_isblank(s[i]) && ++non_blank)
		{
			if (is_lit(s[i], &lit_status) || !is_operator(s[i]))
				set_operators_as_used(&lit_status);
			else if (is_operator(s[i])
				&& is_operator_repeted(&lit_status, s, &i))
				return (&(s[i]) + (s[i + i] = '\0'));
			else
				set_operators_as_used(&lit_status);
		}
	}
	if (non_blank
		&& (lit_status.quote || lit_status.dquote || lit_status.pipe))
		return ("newline");
	return (NULL);
}
