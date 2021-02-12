#include "minishell.h"

int
    exec_init_cmd_data(t_cmd_data *cmd_data, t_builtin *builtin_data, char *cmd_line)
{

    cmd_data->env_arr = NULL;
    cmd_data->cmd_split = NULL;
    cmd_data->filename = NULL;
    cmd_data->builtin_data = builtin_data;
    if (parse_redirections(cmd_line, cmd_data->redirfd) < 0)
        return (-1);    // should print error message as well
    if (!(cmd_data->cmd_split = parse_argv(cmd_line)))
        return (exec_close_cmd_data(cmd_data) - 1);
    if (exec_set_cmd_filename(cmd_data->cmd_split[0], cmd_data) < 0)
        return (exec_close_cmd_data(cmd_data) - 1);
    if (!(cmd_data->env_arr = env_make_arr(builtin_data->local_env)))
        return (exec_close_cmd_data(cmd_data) - 1);
    return (0);
}