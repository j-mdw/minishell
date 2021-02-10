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
    exec_child(int pipefd[2], t_cmd_data *cmd_data)
{
    reset_signals();
    if (pipefd[0] != 0)
        close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    if (pipefd[1] != 1)
        close(pipefd[1]);
    // Set redir
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

char
    **parse_argv(char *cmd_line)
{
    char **argv;

    argv = ft_split(cmd_line, ' ');
    return (argv);
}

int
    set_cmd_filename(char *cmd, t_cmd_data *cmd_data)
{
    cmd_data->filename = NULL;
    if ((cmd_data->builtin_index = ft_strfind((const char **)cmd_data->builtin_data->builtin_names_arr, cmd)) >= 0)
        return (0);
    if (!(cmd_data->filename = search_path(env_get_val(cmd_data->builtin_data->local_env, "PATH"), cmd)))
        return (-1);
    return (0);
}

int
    close_cmd_data(t_cmd_data *cmd_data)
{
    close_if(cmd_data->redirfd[0], STDIN_FILENO);
    close_if(cmd_data->redirfd[1], STDOUT_FILENO);
    // printf("Cmd|filename|env: %s|%s|%p|%s|%s\n", cmd_data->cmd_split[0], cmd_data->cmd_split[1], cmd_data->env_arr, cmd_data->env_arr[0], cmd_data->env_arr[1]);
    if (cmd_data->cmd_split)
        ft_free_strarr(&(cmd_data->cmd_split));
    if (cmd_data->filename)
        free(cmd_data->filename);
    if (cmd_data->env_arr)
        free(cmd_data->env_arr);
    return (0);
}

int
    init_cmd_data(t_cmd_data *cmd_data, t_builtin *builtin_data, char *cmd_line)
{

    cmd_data->env_arr = NULL;
    cmd_data->cmd_split = NULL;
    cmd_data->filename = NULL;
    cmd_data->builtin_data = builtin_data;
    if (parse_redirections(cmd_line, cmd_data->redirfd) < 0)
        return (-1);    // should print error message as well
    if (!(cmd_data->cmd_split = parse_argv(cmd_line)))
        return (close_cmd_data(cmd_data) - 1);
    if (set_cmd_filename(cmd_data->cmd_split[0], cmd_data) < 0)
        return (close_cmd_data(cmd_data) - 1);
    if (!(cmd_data->env_arr = env_make_arr(builtin_data->local_env)))
        return (close_cmd_data(cmd_data) - 1);
    return (0);
}


int
    exec_pipe(char **pipe_split, int index, int piperead_fildes, t_builtin *builtin_data)
{
    int     stdin_copy;
    int     wstatus;
    int     pipefd[2];
    pid_t   child;
    t_cmd_data cmd_data;

    if (pipe_split[index] == NULL)
        return(EXIT_SUCCESS);
    if (init_cmd_data(&cmd_data, builtin_data, pipe_split[index]) < 0)
        return (-1);
    // printf("Cmd|filename|env: %s|%s|%p|%s|%s\n", cmd_data.cmd_split[0], cmd_data.cmd_split[1], cmd_data.env_arr, cmd_data.env_arr[0], cmd_data.env_arr[1]);
    // printf("cmd split: |%s|%s|\n", cmd_data.cmd_split[0], cmd_data.cmd_split[1]);
    // printf("filename: |%s|\n", cmd_data.filename);
    if (pipe_fd_mng(&stdin_copy, piperead_fildes, pipefd, pipe_split[index + 1]) < 0)
        return (close_cmd_data(&cmd_data) - 1);
    if ((child = fork()) < 0)
    	return(close_cmd_data(&cmd_data) + close_if(pipefd[0], 0) + close_if(pipefd[1], 1) + close(stdin_copy) - 1);
	else if (child == 0)
        exec_child(pipefd, &cmd_data);
    else
    {
        close_if(pipefd[1], STDOUT_FILENO);
        exec_pipe(pipe_split, index + 1, pipefd[0], builtin_data);
        waitpid(child, &wstatus, 0);
        dup2(stdin_copy, STDIN_FILENO);
        close(stdin_copy);
        close_cmd_data(&cmd_data);
    }
    return(WEXITSTATUS(wstatus));
}
