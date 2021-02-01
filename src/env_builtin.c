#include "minishell.h"

int
    env_builtin(char **argv, char **env)
{
    (void)argv;
    if (!env)
        return (EXIT_FAILURE);
    ft_putstrarr(env);
    return (EXIT_SUCCESS);
}