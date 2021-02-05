#include "minishell.h"

static void
    export_print(t_list **env)
{
    char    *ptr;

    while (*env)
    {
        write(STDOUT_FILENO, "declare -x ", 11);
        if (!(ptr = ft_strchr((*env)->content, '=')))
            ft_putstr_fd((*env)->content, STDOUT_FILENO);
        else
        {
            write(STDOUT_FILENO, (*env)->content, ptr - (char *)(*env)->content);
            write(STDOUT_FILENO, "\"", 1);
            ft_putstr_fd((*env)->content + (ptr - (char *)(*env)->content), STDOUT_FILENO);
            write(STDOUT_FILENO, "\"", 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        *env = (*env)->next;
    }
}
/*
** - No arg: print env
** - Arg:
**      - key only: 
**          - if key already exists - do nothing
**          - if key doesnt exist - add a new elem, copy key in content
**      - key=value:
**          - if key exists: free it, dup arg1 in content
**          - if key doesn't exist: create new elem, dup arg1 in content
*/
int
    builtin_export(char **av, t_list **env)
{
    char    *key;
    char    *value;
    int     i;

    if (!av[1])
    {
        export_print(env);
        return (EXIT_SUCCESS);
    }
    // else
    // {
    //     if (!ft_isalpha(av[1][0]) || av[1][0] != '_')
    //     {
    //         printf("minishell : export : '%s' : not a valid identifier\n", env[1]);
    //         return (EXIT_FAILURE);
    //     }
    //     i = 1;
    //     while (av[1][i] != '=' && av[1][i])
    //     {
    //         if (!(ft_isalnum(av[1][i])) || (av[1][i] != '_'))
    //         {
    //             printf("minishell : export : '%s' : not a valid identifier\n", env[1]);
    //             return (EXIT_FAILURE);
    //         }
    //         i++;
    //     }
    //     if(av[1][i])
    //         return (set_envvar);
    //     else
    //     if (*value)
    //     if (!(key = ft_strndup(av[1], i)))
    //         return (EXIT_FAILURE);
    //     if (env_get_val(*env, key) && )
    //     {


    //     }
    //     if (av[1][i])
    //     {
    //         j = 0;
    //         while ()
    //     }
    // }
    // return (EXIT_SUCCESS);
}