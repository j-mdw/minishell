#include "minishell.h"

int
    cd_builtin(char **argv, t_list **env)
{
    (void)env;
    
    return (chdir(argv[1]));
}