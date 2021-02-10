/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_lit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:10:06 by user42            #+#    #+#             */
/*   Updated: 2021/02/10 13:10:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
