#include "minishell.h"

int
    builtin_env(char **argv, t_list **env)
{
    (void)argv;
    if (!(*env))
        return (EXIT_FAILURE);
    env_print(*env);
    return (EXIT_SUCCESS);
}