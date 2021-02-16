#include "minishell.h"

/*
** execute_function forks current process and attempts to execute
** a command based on arguments passed through **arg_split
** The forked process resets signals to default so it can be
** interrupted or quit using SIGINT or SIGQUIT signals
**
** The function returns 0 on success
*/

static int
	exec_bin(char **cmd, char **env, char *filename)
{
	pid_t	child;
	int		wstatus; //arg to wait

	if ((child = fork()) < 0)
		return(-1);
	else if (child == 0)
	{
		reset_signals(); //All signals are reset to DFL during when execve is called
						// So depending on what is done here, may not need to call
						// 'reset_signals()' 
		execve(filename, cmd, env);
		fprintf(stderr, "From exec bin: error %d : %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE); // Not so sure how we should set exit status
	}
	else
	{
		wait(&wstatus); //TBC whether we have to do smth w/ 'wstatus'
	}
	return (WEXITSTATUS(wstatus));
}


int
	exec_function(char **cmd, t_builtin *builtin_data)
{
	int		func_index;
	char	**env_arr;
	char	*filename;
	int		ret;

	if ((func_index = ft_strfind((const char **)builtin_data->builtin_names_arr, cmd[0])) >= 0)
		ret = builtin_data->buitin_func_arr[func_index](cmd, &(builtin_data->local_env));
	else
	{
		if ((env_arr = env_make_arr(builtin_data->local_env)))
		{
			if ((filename = search_path(env_get_val(builtin_data->local_env, "PATH"), cmd[0])))
			{
				ret = exec_bin(cmd, env_arr, filename);
				free(filename);
			}
			free(env_arr);
		}
		else
			return (-1);
	}
	return (ret);
}