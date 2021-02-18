#include "termcaps.h"

int
    tty_error(char *error_msg)
{
    dprintf(STDERR_FILENO, "Error: %s: %s\n", error_msg, strerror(errno));
    return (-1);
}