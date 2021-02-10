#include "minishell.h"

// int
//     exec_builtin(t_builtin *builtin_data)
// {
//     int func_index;

//     if ((func_index = ft_strfind((const char **)builtin_data->builtin_names_arr, builtin_data->cmd[0])) >= 0)
// 	    return(builtin_data->builtin_func_arr[func_index](builtin_data->cmd, &(builtin_data->local_env)));
//     return (-1);
// }

// int
//     exec_bin(t_builtin *builtin_data)
// {

    // if ((builtin_data->env_arr = env_make_arr(builtin_data->local_env)))
    // {
    //     if ((builtin_data->filename = search_path(env_get_val(builtin_data->local_env, "PATH"), builtin_data->cmd[0])))
    //         execve(builtin_data->filename, builtin_data->cmd, builtin_data->env_arr); // Filename and env_var not freed if execve is executed
    // }
    // fprintf(stderr, "From exec bin: error %d : %s\n", errno, strerror(errno));
    // return (EXIT_FAILURE);
// }

static int
    pipe_fd_mng(int *stdin_cpy, int piperead_fildes, int pipefd[2], char *next_cmd)
{
    if ((*stdin_cpy = dup(STDIN_FILENO)) < 0)
        return (-1);       
    if (dup2(piperead_fildes, STDIN_FILENO) < 0)
        return (-1);
    if (piperead_fildes != 0)
        close(piperead_fildes);
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
    exec_child(char *cmd_line, int pipefd[2], t_builtin *builtin_data)
{
    reset_signals();
    if (pipefd[0] != 0)
        close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    if (pipefd[1] != 1)
        close(pipefd[1]);
    // Set redir
    if (builtin_data->builtin_index >= 0)
        exit((builtin_data->builtin_func_arr[builtin_data->builtin_index]
        (builtin_data->cmd, &(builtin_data->local_env))));
    else
    {
        execve(builtin_data->filename, builtin_data->cmd, builtin_data->env_arr);
        dprintf(STDERR_FILENO, "Error: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

char
    **parse_argv(char *cmd_line)
{
    char **argv;

    argv = ft_split(cmd_line, ' ');
    return (argv);
}

char
    *set_cmd_filename(char *cmd, t_builtin *builtin_data)
{
    builtin_data->filename = NULL;
    if ((builtin_data->builtin_index = ft_strfind((const char **)builtin_data->builtin_names_arr, builtin_data->cmd[0])) >= 0)
        return (0);
    if (!(builtin_data->filename = search_path(env_get_val(builtin_data->local_env, "PATH"), cmd)))
        return (-1);
    return (0);
}

int
    close_exec_data(t_builtin *builtin_data)
{
    close_if(builtin_data->redirfd[0], STDIN_FILENO);
    close_if(builtin_data->redirfd[1], STDOUT_FILENO);
    // close_if(builtin_data->pipefd[0], STDIN_FILENO);
    // close_if(builtin_data->pipefd[1], STDOUT_FILENO);
    if (builtin_data->cmd)
        ft_free_strarr(&(builtin_data->cmd));
    if (builtin_data->filename)
        free(builtin_data->filename);
    if (builtin_data->env_arr)
        ft_free_strarr(&(builtin_data->env_arr));
}

int
    init_exec_data(t_builtin *builtin_data, char *cmd_line)
{

    builtin_data->env_arr = NULL;
    builtin_data->cmd = NULL;
    builtin_data->filename = NULL;
    // builtin_data->pipefd[0] = STDIN_FILENO;
    // builtin_data->pipefd[1] = STDOUT_FILENO;
    if (parse_redirections(cmd_line, builtin_data->redirfd) < 0)
        return (-1);    // should print error message as well
    if (!(builtin_data->cmd = parse_argv(cmd_line)))
        return (close_exec_data(builtin_data) -1);
    if (set_cmd_filename(builtin_data->cmd[0], builtin_data) < 0)
        return (close_exec_data(builtin_data) -1);
    if (!(builtin_data->env_arr = env_make_arr(builtin_data->local_env)))
        return (close_exec_data(builtin_data) -1);
}
int
    exec_pipe(char **pipe_split, int index, int piperead_fildes, t_builtin *builtin_data)
{
    int     stdin_copy;
    int     wstatus;
    int     pipefd[2];
    pid_t   child;

    if (pipe_split[index] == NULL)
        return(EXIT_SUCCESS);
    if (init_exec_data(builtin_data, pipe_split[index]) < 0)
        return (-1);
    if (pipe_fd_mng(&stdin_copy, piperead_fildes, pipefd, pipe_split[index + 1]) < 0)
        return (close_exec_data(builtin_data) - 1);
    if ((child = fork()) < 0)
    	return(close_exec_data(builtin_data) + close_if(pipefd[0], 0) + close_if(pipefd[1], 1) + close(stdin_copy) - 1);
	else if (child == 0)
        exec_child(pipe_split[index], pipefd, builtin_data);
    else
    {
        close_if(pipefd[1], STDOUT_FILENO);
        exec_pipe(pipe_split, index + 1, pipefd[0], builtin_data);
        waitpid(child, &wstatus, 0);
        dup2(stdin_copy, STDIN_FILENO);
        close(stdin_copy);
        close_exec_data(builtin_data);
    }
    return(WEXITSTATUS(wstatus));
}
