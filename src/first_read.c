/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:38:35 by user42            #+#    #+#             */
/*   Updated: 2021/02/11 14:12:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#include <string.h>

typedef struct	s_lit_status {
		int				quote;
		int				dquote;
		int				backs;
}				t_lit_status;


int
	ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int		is_lit(char c, t_lit_status *lit_status)
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

char		*first_read(char *str)
{
	int				i;
	t_lit_status	lit_status;
	int				unused_op;
	int				non_blank;
	int				pipe;
	int				lit;

	i = -1;
	lit_status.quote = 0;
	lit_status.dquote = 0;
	lit_status.backs = 0;
	unused_op = 1;
	non_blank = 0;
	pipe = 0;
	while (str[++i])
	{
		non_blank += !ft_isblank(str[i]);
		if (!(lit = is_lit(str[i], &lit_status)))
		{
			if ((str[i] == '|' || str[i] == ';') && (++unused_op > 1))
				return (&(str[i]) + (str[i + 1] = '\0'));
			// else if (!ft_isblank(str[i]) && str[i] != '|' && str[i] != ';' \
			// 	&& ((pipe = 0) < unused_op))
			// 	unused_op = 0;
			else if (str[i] == '|')
				pipe = 1;
		}
		else if (!ft_isblank(str[i]) && ((pipe = 0) < unused_op))
			unused_op = 0;
	}
	if (non_blank && (lit_status.quote || lit_status.dquote || pipe))
		return ("newline");
	return (NULL);
}
