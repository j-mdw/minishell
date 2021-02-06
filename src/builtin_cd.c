#include "minishell.h"

int
    builtin_cd(char **av, t_list **env)
{
    char    *path;

    (void)env;
    if (!av[1])
    {
        if (!(path = env_get_val(*env, "HOME")))            //get_val returns NULL if "HOME" doesn't exist or if there's no value associated to the key
        {
            printf("minishell: cd: 'HOME' undefined\n");
            return (EXIT_FAILURE);
        }
    }
    else
        path = av[1];
    if (chdir(path) < 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}