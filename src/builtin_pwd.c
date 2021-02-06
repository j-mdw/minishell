#include "minishell.h"

int
    builtin_pwd(char **argv, t_list **env)
{
    char *current_path;

    (void)argv;
    (void)env;
    current_path = getcwd(NULL, 0);
    ft_putstr_fd(current_path, STDOUT_FILENO);
    write(STDOUT_FILENO, "\n", 1);
    free(current_path);
    return (0);
}

// main(){
//     pwd_builtin(NULL, NULL);
// }