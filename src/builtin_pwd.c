#include "minishell.h"

int
    builtin_pwd(char **argv, t_list **env)
{
    char *current_path;

    (void)argv;
    (void)env;
    if (!(current_path = getcwd(NULL, 0)))
    {
        printf("error: pwd: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    ft_putstr_fd(current_path, STDOUT_FILENO);
    write(STDOUT_FILENO, "\n", 1);
    free(current_path);
    return (EXIT_SUCCESS);
}