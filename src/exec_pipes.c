/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:17:10 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/15 17:13:18 by jmaydew          ###   ########.fr       */
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

static void
	exec_child(int pipefd[2], int readfd, t_cmd_data *cmd_data)
{
	// set_child_signals();
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

static int
	exec_builtin(t_cmd_data *cmd_data)
{
	int ret;
	int stdin_cpy;
	int stdout_cpy;

	if ((stdin_cpy = dup(STDIN_FILENO)) < 0)
		dprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
	if ((stdout_cpy = dup(STDOUT_FILENO)) < 0)
		dprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
	exec_set_redir(cmd_data->redirfd);
	ret = cmd_data->builtin_data->builtin_func_arr[cmd_data->builtin_index]
(cmd_data->cmd_split, &(cmd_data->builtin_data->local_env));
	if (cmd_data->redirfd[0] != 0)
	{
		if (dup2(stdin_cpy, STDIN_FILENO) < 0)
			dprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
		close(stdin_cpy);
	}
	if (cmd_data->redirfd[1] != 1)
	{
		if (dup2(stdout_cpy, STDOUT_FILENO) < 0)
			dprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
		close(stdout_cpy);
	}
	exec_close_cmd_data(cmd_data);
	g_minishell_exit_status = ret;
	return (0);
}

int
	exec_pipe(char **pipe_split, int index, int piperead_fildes,
	t_builtin *builtin_data)
{
	int		wstatus;
	int		pipefd[2];
	pid_t	child;
	t_cmd_data cmd_data;

	if (pipe_split[index] == NULL)
		return(EXIT_SUCCESS);
	if (exec_init_cmd_data(&cmd_data, builtin_data, pipe_split[index]) < 0)
		return (-1);
	if (!pipe_split[1] && cmd_data.builtin_index >= 0)
		return (exec_builtin(&cmd_data));
	if (pipe_open_if(pipefd, pipe_split[index + 1]) < 0)
		return (exec_close_cmd_data(&cmd_data) - 1);
	if ((child = fork()) < 0)
		return(exec_close_cmd_data(&cmd_data) + close_if(pipefd[0], 0) +
		close_if(pipefd[1], 1));
	else if (child == 0)
		exec_child(pipefd, piperead_fildes, &cmd_data);
	else
	{
		set_parent_signals();
		close_if(piperead_fildes, 0);
		close_if(pipefd[1], STDOUT_FILENO);
		exec_pipe(pipe_split, index + 1, pipefd[0], builtin_data);
		waitpid(child, &wstatus, 0);
		set_signals();
		exec_close_cmd_data(&cmd_data);
		if (!pipe_split[index + 1])
			g_minishell_exit_status = WEXITSTATUS(wstatus);
	}
	return(0);
}
