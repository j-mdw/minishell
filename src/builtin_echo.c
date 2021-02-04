#include "minishell.h"

int
    echo_builtin(char **arg, t_list **env)
{
    int n_flag;
    int i;

    (void)env;
    n_flag = 0;
    if (!(ft_strcmp(arg[1], "-n")))
        n_flag = 1;
    i = 1 + n_flag;
    while (arg[i])
    {
        write(STDOUT_FILENO, arg[i], ft_strlen(arg[i]));
        if (arg[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (!n_flag)
        write(STDOUT_FILENO, "\n", 1);
    return (EXIT_SUCCESS);
}