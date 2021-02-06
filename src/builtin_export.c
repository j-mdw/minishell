#include "minishell.h"

static void
    export_print(t_list *env)
{
    char    *ptr;

    while (env)
    {
        write(STDOUT_FILENO, "declare -x ", 11);
        if (!(ptr = ft_strchr(env->content, '=')))
            ft_putstr_fd(env->content, STDOUT_FILENO);
        else
        {
            write(STDOUT_FILENO, env->content, ptr - (char *)env->content);
            write(STDOUT_FILENO, "\"", 1);
            ft_putstr_fd(env->content + (ptr - (char *)env->content), STDOUT_FILENO);
            write(STDOUT_FILENO, "\"", 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        env = env->next;
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
    t_list  *elem;
    int     i;

    if (!av[1])
        export_print(*env);
    else
    {
        if (!ft_isalpha(av[1][0]) && av[1][0] != '_')
        {
            printf("minishell : export : '%s' : not a valid identifier\n", av[1]);
            return (EXIT_FAILURE);
        }
        i = 1;
        while (av[1][i] != '=' && av[1][i])
        {
            if (!(ft_isalnum(av[1][i])) && (av[1][i] != '_'))
            {
                printf("minishell :M export : '%s' : not a valid identifier\n", av[1]);
                return (EXIT_FAILURE);
            }
            i++;
        }
        if (!(key = ft_strndup(av[1], i)))
            return (EXIT_FAILURE);
        if (!(elem = env_get_key(*env, key)))
            ft_lstadd_back(env, ft_lstnew(ft_strdup(av[1])));   // lstnew and strdup not protected
        else
        {
            if (av[1][i])
            {
                free(elem->content);
                if (!(elem->content = ft_strdup(av[1])))
                    return (EXIT_FAILURE);
            }
        }
        free(key);
    }
    return (EXIT_SUCCESS);
}