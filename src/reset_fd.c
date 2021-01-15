#include "minishell.h"

/*
** resets reset_fd to save_fd
** closes save_fd
** returns 0 on success, -1 on error
*/

int
    reset_fd(int save_fd, int reset_fd)
{
    if (dup2(save_fd, reset_fd) < 0)               //Set reset_fd to save_fd file description
        return (-1);
    if (close(save_fd) < 0)                                // Close save_fd
        return (-1);
    return (0);
}