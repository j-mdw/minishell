#include "minishell.h"

/*
** sets start_fd to new_fd
** returns copy of start_fd
*/

int
    set_fd(int start_fd, int set_fd)
{
    int save_fd;

    if ((save_fd = dup(start_fd)) < 0)        //copy start_fd in save_fd
        return (-1);
    if (dup2(set_fd, start_fd) < 0)               //Set start_fd to set_fd file description
        return (-1);
    return (save_fd);
}