#include "minishell.h"

int
    builtin_exit(char **cmd, t_list **env)
{
    (void)cmd;
    (void)env;
    exit(EXIT_SUCCESS);
    // NEED TO FREE EVERYTHING..
}