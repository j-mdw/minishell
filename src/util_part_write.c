/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_part_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 02:35:22 by user42            #+#    #+#             */
/*   Updated: 2021/02/28 02:36:58 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*part_write(t_exp_utils *utils, char *value_str, int i)
{
	if (!utils->final_param)
		return (NULL);
	while (i-- > 0)
	{
		utils->final_param--;
		utils->raw_param--;
		if (!value_str)
			*utils->final_param = *utils->raw_param;
		else
			*utils->final_param = value_str[i];
	}
	return (utils->final_param);
}
