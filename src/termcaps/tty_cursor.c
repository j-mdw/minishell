#include "termcaps.h"

int
    tty_init_cursor_pos(t_cursor_pos *cursor_pos)
{
    if (tty_get_cursor_pos(cursor_pos) < 0)
        return (-1);
    cursor_pos->start_col = cursor_pos->col;
    cursor_pos->start_row = cursor_pos->row;
    cursor_pos->max_col = cursor_pos->col;
    cursor_pos->max_row = cursor_pos->row;
    return (0);
}

int
    tty_get_cursor_pos(t_cursor_pos *cursor_pos)
{
    char    buf[32];
    int     read_ret;
    int     i;

    write(STDIN_FILENO, "\x1b[6n", 4);
    if ((read_ret = read(STDIN_FILENO, buf, 32)) <= 0)
        return(tty_error("read error"));
    buf[read_ret] = '\0';
    cursor_pos->row = ft_atoi(&buf[2]);
    i = 2;
    while (buf[i] != ';' && buf[i])
        i++;
    if (!buf[i])
    {
        dprintf(STDERR_FILENO, "no cursor column provided");
        return (-1);
    }
    cursor_pos->col = ft_atoi(&buf[i + 1]);
    return (0);
}