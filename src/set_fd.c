#include "minishell.h"

/*
** sets newfd to oldfd file description
** returns copy of initial newfd
*/

int
    set_fd(int oldfd, int newfd)
{
    int newfd_cp;

    if ((newfd_cp = dup(newfd)) < 0)        //copy newfd in newfd_cp
        return (-1);
    if (dup2(oldfd, newfd) < 0)               //Set newfd to oldfd file description
        return (-1);
    return (newfd_cp);
}