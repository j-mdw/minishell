/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:50:39 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/19 14:58:45 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*env_get_val(t_list *env, char *key)
{
	char *value;

	while (env)
	{
		if ((value = ft_strchr(env->content, '=')))
		{
			if (!(ft_strncmp(key, env->content, value - (char *)env->content)))
			{
				if (!key[value - (char *)env->content])
					return (value + 1);
			}
		}
		env = env->next;
	}
	return (NULL);
}
