/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_set_cmd_filename.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:50:01 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 21:36:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	exec_set_cmd_filename(char *cmd, t_cmd_data *cmd_data)
{
	cmd_data->filename = NULL;
	if ((cmd_data->builtin_index = ft_strfind((const char **)
	cmd_data->builtin_data->builtin_names_arr, cmd)) >= 0)
		return (0);
	if (!(cmd_data->filename = search_path(env_get_val(
		cmd_data->builtin_data->local_env, "PATH"), cmd)))
		return (-1);
	return (0);
}
