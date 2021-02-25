/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:35:57 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 16:36:29 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	exec_child(int pipefd[2], int readfd, t_cmd_data *cmd_data)
{
	if (!cmd_data->cmd_split[0][0])
		exit(EXIT_SUCCESS);
	if (!cmd_data->filename && cmd_data->builtin_index < 0)
	{
		printf("minishell: command not found: %s\n", cmd_data->cmd_split[0]);
		exit(127);
	}
	if (pipefd[0] != 0)
		close(pipefd[0]);
	if (dup2(readfd, STDIN_FILENO) < 0)
		dprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		dprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
	if (pipefd[1] != 1)
		close(pipefd[1]);
	exec_set_redir(cmd_data->redirfd);
	if (cmd_data->builtin_index >= 0)
		exit((cmd_data->builtin_data->builtin_func_arr[cmd_data->builtin_index]
(cmd_data->cmd_split, &(cmd_data->builtin_data->local_env))));
	else
	{
		execve(cmd_data->filename, cmd_data->cmd_split, cmd_data->env_arr);
		dprintf(STDERR_FILENO, "Error (after execve): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
