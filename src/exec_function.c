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
	exec_bin(char **cmd, char **env)
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
		fprintf(stderr, "From exec builtin: error %d : %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE); // Not so sure how we should set exit status
	}
	else
	{
		wait(&wstatus); //TBC whether we have to do smth w/ 'wstatus'
		free(file_path);
	}
	return (WEXITSTATUS(wstatus));
}

void
	init_binfunc_arr(t_binfunc_arr *binfunc_arr)
{
	binfunc_arr[0] = echo_builtin;
	binfunc_arr[1] = exit_builtin;
}

char
	**init_builtin_names_arr(void)
{
	char **arr;
	
	arr = (char **)malloc(sizeof(char *) * BUILTIN_COUNT + 1);

	arr[0] = ft_strdup("echo");
	arr[1] = ft_strdup("exit");
	arr[2] = ft_strdup("pwd");
	arr[3] = NULL;
	return (arr);
}

int
	exec_function(char **cmd, char **env)
{
	int						func_index;
	static t_binfunc_arr	func_arr[BUILTIN_COUNT];
	char 					**builtin_names;
	int						ret;
	
	builtin_names = init_builtin_names_arr();
	if ((func_index = ft_strfind((const char **)builtin_names, cmd[0])) >= 0)
	{
		init_binfunc_arr(func_arr);
		ret = func_arr[func_index](cmd, env);
	}
	else
		ret = exec_bin(cmd, env);
	ft_freestrarr(builtin_names, BUILTIN_COUNT);
	return (ret);
}