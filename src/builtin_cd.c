#include "minishell.h"

/*
** No arg
**      - Look for HOME variable
**         - If it exists and has a =value, chdir to HOME
**         - Else, print error message and return
** Arg:
**      
**      - chdir to arg
**      - If error, print message and return
** chdir returned 0:
**  - Look for OLDPWD - if it exists, free it
**  - Look for PWD - if it exists:
**      - get value, merge with OLDPWD=, set OLDPWD to it
**      - set PWD to strdup(new_path)
*/

static int
    cd_set_envvar(t_list *env)
{
    t_list  *oldpwd;
    t_list  *newpwd;
    char    *ptr;

    if ((oldpwd = env_get_key(env, "OLDPWD")))
    {
        free(oldpwd->content);
        if ((ptr = env_get_val(env, "PWD")))
        {
            if (!(oldpwd->content = ft_strjoin("OLDPWD=", ptr)))
                return (-1);
        }
        else
            if (!(oldpwd->content = ft_strdup("OLDPWD")))
                return (-1);          
    }
    if ((newpwd = env_get_key(env, "PWD")))
    {
        free(newpwd->content);
        ptr = getcwd(NULL, 0);
        if (!(newpwd->content = ft_strjoin("PWD=", ptr)))
            return (-1);
    }
    return (EXIT_SUCCESS);
}

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
    {
        printf("minishell: cd: %s: no such file or directory\n", path);
        return (EXIT_FAILURE);
    }
    return (cd_set_envvar(*env));
}