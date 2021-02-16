/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lit_status_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:12:34 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 14:12:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		lit_status_init(t_lit_status *lit_status)
{
	lit_status->quote = 0;
	lit_status->dquote = 0;
	lit_status->backs = 0;
	lit_status->unused_op = 1;
	lit_status->pipe = 0;
	lit_status->redir = 0;
}
