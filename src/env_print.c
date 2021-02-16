/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:18:06 by user42            #+#    #+#             */
/*   Updated: 2021/02/14 13:18:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	env_print(t_list *local_env)
{
	while (local_env)
	{
		printf("%s\n", (char *)local_env->content);
		local_env = local_env->next;
	}
}
