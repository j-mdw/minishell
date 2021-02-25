/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_is_lit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:10:06 by user42            #+#    #+#             */
/*   Updated: 2021/02/25 16:16:03 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_lit(char c, t_lit_status *lit_status)
{
	if (!lit_status->quote && !lit_status->backs)
	{
		lit_status->quote = (c == '\'');
		lit_status->dquote = ((c != '\"' && lit_status->dquote)
			|| (c == '\"' && !lit_status->dquote));
		lit_status->backs = (c == '\\');
		return (0);
	}
	if (lit_status->backs)
		return ((lit_status->backs = 0) + 1);
	lit_status->quote -= ((c == '\'') && lit_status->quote);
	return (lit_status->quote);
}