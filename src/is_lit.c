/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_lit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:10:06 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 22:24:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_lit(char c, t_lit_status *lit_status)
{
printf("char: %c ", c);
	if (!lit_status->quote && !lit_status->backs)
	{
		lit_status->quote = (c == '\'');
		lit_status->dquote = ((c != '\"' && lit_status->dquote)
			||  (c == '\"' && !lit_status->dquote));
		lit_status->backs = (c == '\\');
printf("0\n");
		return (0);
	}
	if (lit_status->backs)
	{
printf("1\n");
		return ((lit_status->backs = 0) + 1);
	}
	lit_status->quote -= ((c == '\'') && lit_status->quote);
printf("%d\n", lit_status->quote);
	return (lit_status->quote);
}
