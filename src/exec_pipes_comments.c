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
    int ret = 0;
    if ((func_index = ft_strfind((const char **)builtin_data->builtin_names_arr, cmd[0])) >= 0)
    {
        // printf("Found it! %d\n", func_index);
	    ret = (builtin_data->builtin_func_arr[func_index](cmd, &(builtin_data->local_env)));
        return (ret);
        // printf("Builtin ret: %d\n", ret);

    }
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

    // printf("Pipe split: |%s|%s|\n", pipe_split[0], pipe_split[1]);
    // printf("Func inputs: index: |%d| piperead_fildes: |%d|\n", index, piperead_fildes);
    if (pipe_split[index] == NULL)
        return(EXIT_SUCCESS);
    builtin_data->env_arr = NULL;
    builtin_data->filename = NULL;
    stdin_copy = dup(STDIN_FILENO);         //  STDIN, STDOUT, STDIN_CPY, piperead_fildes
    dup2(piperead_fildes, STDIN_FILENO);    //  close(STDIN) - STDOUT, STDIN_CPY, piperead_fildes, piperead_fildes_copy (=0)
    if (piperead_fildes != 0)
        close(piperead_fildes);             // close piperead_fildes - STDOUT, STDIN_CPY, piperead_fildes_copy (=0)
    if (pipe_split[index + 1])
        pipe(pipefd);                       // + pipe - STDOUT, STDIN_CPY, piperead_fildes_copy (=0), pipe[0], pipe[1]
    else
    {
        pipefd[0] = 0;
        pipefd[1] = 1;
    }
    // printf("cmd split\n");
    cmd = ft_split(pipe_split[index], ' '); // do in child as redir have to be done before this?
    // printf("cmd split: |%s|%s|\n", cmd[0], cmd[1]);
    if ((child = fork()) < 0)
		return(-1);
	else if (child == 0)
    {
        if (pipefd[0] != 0)
            close(pipefd[0]);
        // printf("Inside childs\n");
        reset_signals();
        dup2(pipefd[1], STDOUT_FILENO);     // + pipe[1]_cpy, close STDOUT - STDIN_CPY, piperead_fildes_copy (=0), pipe[0], pipe[1], pipe[1]_cpy (=1)
        if (pipefd[1] != 1)
            close(pipefd[1]);               // close pipe[1] - STDIN_CPY, piperead_fildes_copy (=0), pipe[0], pipe[1]_cpy (=1)
        // set redir < >
        // cmd = parse_cmd(pipe_split[index]);
        if (exec_builtin(builtin_data, cmd) >= 0)
            exit(EXIT_SUCCESS);             //
        else
        {
            exec_bin(cmd, builtin_data);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        close(pipefd[1]);
        exec_pipe(pipe_split, index + 1, pipefd[0], builtin_data);
        // printf("Before waitpid\n");
        waitpid(child, &wstatus, 0);
        // printf("After waitpid\n");
        dup2(stdin_copy, STDIN_FILENO);
        close(stdin_copy);
        free(builtin_data->filename);
        ft_free_strarr(&cmd);
        if (builtin_data->env_arr)
            ft_free_strarr(&(builtin_data->env_arr));
    }
    return(WEXITSTATUS(wstatus));
}
