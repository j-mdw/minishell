#include "minishell.h"
// #include <limits.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <fcntl.h>
// #include <stdlib.h>

// void
// 	ft_putstr_fd(char *s, int fd)
// {
// 	size_t	s_len;

// 	if (s && fd > 0)
// 	{
// 		s_len = strlen(s);
// 		write(fd, s, s_len);
// 	}
// }
int
    pwd_builtin(char **argv, char **env)
{
    char *current_path;

    (void)argv;
    (void)env;
    current_path = getcwd(NULL, 0);
    ft_putstr_fd(current_path, STDOUT_FILENO);
    write(STDOUT_FILENO, "\n", 1);
    return (0);
}

// main(){
//     pwd_builtin(NULL, NULL);
// }