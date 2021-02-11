#include "minishell.h"

int
    exec_close_cmd_data(t_cmd_data *cmd_data)
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

