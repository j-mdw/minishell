/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_cmd_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:16:29 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/26 13:32:04 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	exec_init_cmd_data(t_cmd_data *cmd_data, t_builtin *builtin_data, \
	char *cmd_line)
{
	t_lit_status	lit_status;

	lit_status_init(&lit_status);
	cmd_data->env_arr = NULL;
	cmd_data->cmd_split = NULL;
	cmd_data->filename = NULL;
	cmd_data->builtin_data = builtin_data;
	if (parse_redirections(cmd_line, cmd_data->redirfd, &lit_status,
		builtin_data->local_env) < 0)
		return (-1);
	if (!(cmd_data->cmd_split = parse_argv(cmd_line,
		builtin_data->local_env, 0)))
		return (exec_close_cmd_data(cmd_data) - 1);
	exec_set_cmd_filename(cmd_data->cmd_split[0], cmd_data);
	if (!(cmd_data->env_arr = env_make_arr(builtin_data->local_env)))
		return (exec_close_cmd_data(cmd_data) - 1);
	return (0);
}
