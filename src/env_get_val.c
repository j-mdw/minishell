/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:50:39 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/19 15:11:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*env_get_val(t_list *env, char *key)
{
	char *value;

	if (!key)
		return (NULL);
	while (env)
	{
		if ((value = ft_strchr(env->content, '=')))
		{
			if (!(ft_strncmp(key, env->content, value - (char *)env->content)))
				return (value + 1);
		}
		env = env->next;
	}
	return (NULL);
}
