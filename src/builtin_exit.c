#include "minishell.h"

int
    exit_builtin(char **cmd, t_list **env)
{
    (void)cmd;
    (void)env;
    exit(EXIT_SUCCESS);
}