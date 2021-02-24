#include "termcaps.h"

/*
** Only gets escape sequences starting with [ and ending with a char
*/
int
    tty_get_escape_seq(char *buf)
{
    int     i;

    buf[0] = '\x1b';
    i = 1;
    if (read(STDIN_FILENO, &buf[i], 1) < 0)
        return(tty_error("read"));
    if (buf[i] == '[')
    {
        while (!ft_isalpha(buf[i]))
        {
            i++;
            if (read(STDIN_FILENO, &buf[i], 1) < 0)
                return(tty_error("read"));
        }
        return (0);
    }
    return (tty_error("Unknown escape sequence"));
}