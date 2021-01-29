#include "minishell.h"

/*
** execute_builtin forks current process and attempts to execute
** a command based on arguments passed through **arg_split
** The forked process resets signals to default so it can be
** interrupted or quit using SIGINT or SIGQUIT signals
**
** The function returns 0 on success
*/

int
	exec_builtin(char **arg_split)
{
	pid_t	child;
	int		wstatus; //arg to wait
	char	*file_path;
	
	file_path = NULL;
	if ((child = fork()) < 0)
		fprintf(stderr, "From fork: %s\n", strerror(errno));
	else if (child == 0)
	{
		reset_signals(); //All signals are reset to DFL during when execve is called
						// So depending on what is done here, may not need to call
						// 'reset_signals()' 
		if ((file_path = ft_strjoin(BIN_PATH, arg_split[0])) == NULL)
		{
			printf("Join error\n");
			return (-1);
		}
		execve(file_path, arg_split, NULL);
		fprintf(stderr, "From exec builtin: %s\n", strerror(errno));
		exit(EXIT_FAILURE); // Not so sure how we should set exit status
	}
	else
	{
		wait(&wstatus); //TBC whether we have to do smth w/ 'wstatus'
		free(file_path);
	}
	return (WEXITSTATUS(wstatus));
}