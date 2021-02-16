#include "minishell.h"

void
    exec_set_redir(int redirfd[2])
{
    if (redirfd[0] != STDIN_FILENO)
    {
        if (dup2(redirfd[0], STDIN_FILENO) < 0)
            dprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
    }
    if (redirfd[1] != STDOUT_FILENO)
    {
        if (dup2(redirfd[1], STDOUT_FILENO) < 0)
            dprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
    }
}