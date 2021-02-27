/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_init_data_struct.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:49:22 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/27 16:23:19 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	builtin_init_data_struct(t_builtin *builtin_data, char **env)
{
	builtin_data->local_env = env_create_list(env);
	if (!(builtin_data->builtin_names_arr = builtin_init_names_arr()))
	{
		ft_lstclear(&(builtin_data->local_env), free);
		return (-1);
	}
	builtin_init_funcarr(builtin_data->builtin_func_arr);
	return (0);
}
