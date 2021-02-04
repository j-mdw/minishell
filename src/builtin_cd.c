#include "minishell.h"

int
    builtin_cd(char **argv, t_list **env)
{
    (void)env;
    
    return (chdir(argv[1]));
}