#include "minishell.h"

/*
** execute_function forks current process and attempts to execute
** a command based on arguments passed through **arg_split
** The forked process resets signals to default so it can be
** interrupted or quit using SIGINT or SIGQUIT signals
**
** The function returns 0 on success
*/

int
	exec_builtin(char **cmd, char **env)
{
	pid_t	child;
	int		wstatus; //arg to wait
	char	*file_path;

	file_path = NULL;
	if ((child = fork()) < 0)
		return(-1);
	else if (child == 0)
	{
		reset_signals(); //All signals are reset to DFL during when execve is called
						// So depending on what is done here, may not need to call
						// 'reset_signals()' 
		if ((file_path = ft_strjoin(BIN_PATH, cmd[0])) == NULL)
			return (-1);
		execve(file_path, cmd, env);
		// fprintf(stderr, "From exec builtin: error %d : %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE); // Not so sure how we should set exit status
	}
	else
	{
		wait(&wstatus); //TBC whether we have to do smth w/ 'wstatus'
		free(file_path);
	}
	return (WEXITSTATUS(wstatus));
}

int
	exec_function(char **cmd, char **env)
{
	if (!ft_strncmp(cmd[0], "exit", 4))
		return (echo(cmd));
	else
		return (exec_builtin(cmd, env));
}