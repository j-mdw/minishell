/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:49:47 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/14 12:49:48 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list
	*env_get_key(t_list *env, char *key)
{
	int key_len;

	key_len = ft_strlen(key);
	while (env)
	{
		if (!(ft_strncmp(key, env->content, key_len)))
			return (env);
		env = env->next;
	}
	return (NULL);
}
