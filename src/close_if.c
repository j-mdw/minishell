#include "minishell.h"

/*
** Close_if: close fd specified as arg1
** if it is different from value in arg2
** return 0
*/
int
    close_if(int fd1, int diff)
{
    if (fd1 != diff)
        close(fd1);
    return (0);
}