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
		fprintf(stderr, "%s\n", strerror(errno));
	else if (child == 0)
	{
		reset_signals();
		if ((file_path = ft_strjoin(BIN_PATH, arg_split[0])) == NULL)
		{
			printf("Join error\n");
			return (-1);
		}
		execve(file_path, arg_split, NULL);
		fprintf(stderr, "%s\n", strerror(errno));
		exit(0); // Not so sure how we should set exit status
	}
	else
	{
		wait(&wstatus); //TBC whether we have to do smth w/ 'wstatus'
		free(file_path);
	}
	return (0);
}