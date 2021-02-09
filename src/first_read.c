/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:38:35 by user42            #+#    #+#             */
/*   Updated: 2021/02/09 16:02:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		first_read(const char *str)
{
	int				i;
	t_lit_status	lit_status;
	int				unused_operator;
	
	i = 0;
	lit_status.quote = 0;
	lit_status.dquote = 0;
	lit_status.backs = 0;
	unused_operator = 1;
	while (str[i])
	{
		if (!is_lit(str[i], &lit_status))
		{
			if ((str[i] == '|' || str[i] == ';') && unused_operator)
				return (str[i]);
			else if (!ft_isblank(str[i]))
				unused_operator = 0;
		}
		++i;
	}
	if (lit_status.quote || lit_status.dquote ||)
	return (0);
}
