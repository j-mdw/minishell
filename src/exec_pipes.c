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

int
    exec_builtin(t_builtin *builtin_data, char **cmd)
{
    int func_index;
        
    if ((func_index = ft_strfind((const char **)builtin_data->builtin_names_arr, cmd[0])) >= 0)
	    return (builtin_data->buitin_func_arr[func_index](cmd, &(builtin_data->local_env)));
    return (-1);
}

int
    exec_pipe(char **pipe_split, int index, int piperead_fildes, t_builtin *builtin_data)
{
    int     stdin_copy;
    int     pipefd[2];
    char    **cmd;
    pid_t   child;

    if (pipe_split[index] == NULL)
        return(EXIT_SUCCESS);

    stdin_copy = dup(STDIN_FILENO);
    dup2(piperead_fildes, STDIN_FILENO);    
    if (pipe_split[index + 1])
        pipe(pipefd);
	if ((child = fork()) < 0)
		return(-1);
	else if (child == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        // set redir < >
        cmd = parse_cmd(pipe_split[index]);
        if (exec_builtin(builtin_data, cmd) > 0)
            exit(EXIT_SUCCESS)
        else
            name = search path
            execve
            exit()
    else
        exec_pipe(split, i + 1)
        waitpid(childpid)
        close(pipe_fd[1]);
        reset_stdin

        return
}