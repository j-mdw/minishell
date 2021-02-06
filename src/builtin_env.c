#include "minishell.h"

int
    builtin_env(char **argv, t_list **env)
{
    t_list  *iter;

    (void)argv;
    iter = *env;
    if (!(*env))
        return (EXIT_FAILURE);
    while (iter)
    {
        if (ft_strchr(iter->content, '='))
            printf("%s\n", (char *)iter->content);
        iter = iter->next;
    }
    return (EXIT_SUCCESS);
}