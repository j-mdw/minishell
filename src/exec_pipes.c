/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:45:27 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 13:53:42 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	pipe_open_if(int pipefd[2], char *next_cmd)
{
	if (next_cmd)
	{
		if (pipe(pipefd) < 0)
			return (-1);
	}
	else
	{
		pipefd[0] = STDIN_FILENO;
		pipefd[1] = STDOUT_FILENO;
	}
	return (0);
}

static int
	exec_setup(char **pipe_split, t_cmd_data *cmd_data, int index)
{
	int child;

	if (pipe_open_if(cmd_data->pipefd, pipe_split[index + 1]) < 0)
		return (exec_close_cmd_data(cmd_data) - 1);
	if ((child = fork()) < 0)
	{
		return (exec_close_cmd_data(cmd_data)
		+ close_if(cmd_data->pipefd[0], 0) + close_if(cmd_data->pipefd[1], 1));
	}
	return (child);
}

int
	exec_pipe(char **pipe_split, int index, int piperead_fildes,
	t_builtin *builtin_data)
{
	int			wstatus;
	pid_t		child;
	t_cmd_data	cmd_data;

	if (pipe_split[index] == NULL)
		return (EXIT_SUCCESS);
	if (exec_init_cmd_data(&cmd_data, builtin_data, pipe_split[index]) < 0)
		return (-1);
	if (!pipe_split[1] && cmd_data.builtin_index >= 0)
		return (exec_builtin(&cmd_data));
	if ((child = exec_setup(pipe_split, &cmd_data, index)) < 0)
		return (-1);
	else if (child == 0)
		exec_child(cmd_data.pipefd, piperead_fildes, &cmd_data);
	else
	{
		set_parent_signals();
		close_if(piperead_fildes, 0);
		close_if(cmd_data.pipefd[1], STDOUT_FILENO);
		exec_pipe(pipe_split, index + 1, cmd_data.pipefd[0], builtin_data);
		waitpid(child, &wstatus, 0);
		set_signals();
		exec_close_cmd_data(&cmd_data);
		if (!pipe_split[index + 1] && !WIFSIGNALED(wstatus))
			g_minishell_exit_status = WEXITSTATUS(wstatus);
	}
	return (0);
}
