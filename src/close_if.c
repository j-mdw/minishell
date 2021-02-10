#include "minishell.h"

int
    close_if(int fd1, int diff)
{
    if (fd1 != diff)
        close(fd1);
    return (0);
}