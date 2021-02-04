#include "minishell.h"

int
    builtin_export(char **av, t_list **env)
{
    char    *ptr;

    if (!av[1])
    {
        while (*env)
        {
            write(STDOUT_FILENO, "declare -x ", 11);
            if (!(ptr = ft_strchr((*env)->content, "=")))
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
}