/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:49:30 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/14 12:49:32 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list
	*env_create_list(char **env)
{
	t_list	*local_env;
	t_list	*new_elem;
	int		i;

	i = 0;
	local_env = NULL;
	while (env[i])
	{
		if (!(new_elem = ft_lstnew(ft_strdup(env[i]))))
		{
			ft_lstclear(&local_env, free);
			return (NULL);
		}
		ft_lstadd_back(&local_env, new_elem);
		i++;
	}
	return (local_env);
}
