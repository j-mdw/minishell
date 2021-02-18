#include "termcaps.h"

int
    tty_write_over(char *read_buf, char c)
{
    int len;

    len = ft_strlen(read_buf);
    ft_memmove(read_buf + 1, read_buf, len);
    read_buf[len + 1] = '\0';
    *read_buf = c;
    write(STDIN_FILENO, read_buf, len + 1);
    if (tty_move_left(len) < 0)
        return (-1);
    return (0);
}