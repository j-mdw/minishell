#include "minishell.h"

int
    env_builtin(char **argv, t_list **env)
{
    (void)argv;
    if (!(*env))
        return (EXIT_FAILURE);
    env_print(*env);
    return (EXIT_SUCCESS);
}