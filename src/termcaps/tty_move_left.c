#include "termcaps.h"

int
    tty_move_left(int n)
{
    char *rep;

    if (!(rep = ft_itoa(n)))
        return(tty_error("move left: itoa"));
    write(STDIN_FILENO, "\x1b[", 2);
    write(STDIN_FILENO, rep, ft_strlen(rep));
    free(rep);
    write(STDIN_FILENO, "D", 1);
}