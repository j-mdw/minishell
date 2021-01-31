#include "minishell.h"

int
    echo_builtin(char **arg, char **env)
{
    int n_flag;

    (void)env;
    n_flag = 0;
    if (!(ft_strcmp(arg[1], "-n")))
        n_flag = 1;
    write(STDOUT_FILENO, arg[1 + n_flag], ft_strlen(arg[1 + n_flag]));
    if (!n_flag)
        write(STDOUT_FILENO, "\n", 1);
    return (EXIT_SUCCESS);
}