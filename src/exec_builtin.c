/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:31:58 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 10:33:37 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	exec_builtin(t_cmd_data *cmd_data)
{
	int stdin_cpy;
	int stdout_cpy;

	if ((stdin_cpy = dup(STDIN_FILENO)) < 0)
		printf("Error: %s\n", strerror(errno));
	if ((stdout_cpy = dup(STDOUT_FILENO)) < 0)
		printf("Error: %s\n", strerror(errno));
	exec_set_redir(cmd_data->redirfd);
	g_minishell_exit_status =
	cmd_data->builtin_data->builtin_func_arr[cmd_data->builtin_index]
(cmd_data->cmd_split, &(cmd_data->builtin_data->local_env));
	if (cmd_data->redirfd[0] != 0)
	{
		if (dup2(stdin_cpy, STDIN_FILENO) < 0)
			printf("Error: %s\n", strerror(errno));
		close(stdin_cpy);
	}
	if (cmd_data->redirfd[1] != 1)
	{
		if (dup2(stdout_cpy, STDOUT_FILENO) < 0)
			printf("Error: %s\n", strerror(errno));
		close(stdout_cpy);
	}
	exec_close_cmd_data(cmd_data);
	return (0);
}
