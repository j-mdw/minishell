#include "minishell.h"

int
    exit_builtin(char **cmd, char **env)
{
    (void)cmd;
    (void)env;
    exit(EXIT_SUCCESS);
}