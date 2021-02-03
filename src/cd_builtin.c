#include "minishell.h"

int
    cd_builtin(char **argv, char **env)
{
    (void)env;
    
    return (chdir(argv[1]));
}