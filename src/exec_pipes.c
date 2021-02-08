#include "minishell.h"

/*

IF pipe (= if pipe_split + 1 != NULL):
- call pipe recursive function which will run until split[i] is NULL (arg are index and split)
- Waitpid after recursive call
- Pipe fds management? 
ELSE
classic function call

Main diff is that builtins are called in subprocess with pipes -> need a subrposses routine to check 'cmd name' and if not found call execve
*/
/*
int
    exec_builtin(t_builtin *builtin_data, char **cmd)
{
    int func_index;
        
    if ((func_index = ft_strfind((const char **)builtin_data->builtin_names_arr, cmd[0])) >= 0)
	    return (builtin_data->buitin_func_arr[func_index](cmd, &(builtin_data->local_env)));
    return (-1);
}

int
    exec_bin(char **cmd, t_builtin *data)
{

    if ((data->env_arr = env_make_arr(data->local_env)))
    {
        if ((data->filename = search_path(env_get_val(data->local_env, "PATH"), cmd[0])))
        {
            execve(data->filename, cmd, data->env_arr); // Filename and env_var not freed if execve is executed
            free(data->filename);
        }
        free(data->env_arr);
    }
    fprintf(stderr, "From exec bin: error %d : %s\n", errno, strerror(errno));
    return (EXIT_FAILURE);
}

int
    exec_pipe(char **pipe_split, int index, int piperead_fildes, t_builtin *builtin_data)
{
    int     stdin_copy;
    int     pipefd[2];
    char    **cmd;
    int     wstatus;
    pid_t   child;

    if (pipe_split[index] == NULL)
        return(EXIT_SUCCESS);
    builtin_data->env_arr = NULL;
    builtin_data->filename = NULL;
    stdin_copy = dup(STDIN_FILENO);
    dup2(piperead_fildes, STDIN_FILENO);    
    if (pipe_split[index + 1])
        pipe(pipefd);
	cmd = ft_split(pipe_split[index], ' ');
    if ((child = fork()) < 0)
		return(-1);
	else if (child == 0)
    {
        reset_signals();
        dup2(pipefd[1], STDOUT_FILENO);
        // set redir < >
        // cmd = parse_cmd(pipe_split[index]);
        if (exec_builtin(builtin_data, cmd) > 0)
            exit(EXIT_SUCCESS);
        else
        {
            exec_bin(cmd, builtin_data);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        exec_pipe(pipe_split, index + 1, pipefd[0], builtin_data);
        waitpid(child, &wstatus, 0);
        dup2(stdin_copy, STDIN_FILENO);
        free(builtin_data->filename);
        ft_free_strarr(&cmd);
        ft_free_strarr(&(builtin_data->env_arr));
    }
    return(WEXITSTATUS(wstatus));
}
*/