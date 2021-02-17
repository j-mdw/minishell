#include "termcaps.h"

void
    tty_init_cursor_pos(t_cursor_pos *cursor_pos)
{
    tty_get_cursor_pos(cursor_pos);
    cursor_pos->start_col = cursor_pos->col;
    cursor_pos->start_row = cursor_pos->row;
    cursor_pos->max_col = cursor_pos->col;
    cursor_pos->max_row = cursor_pos->row;
}

void
    tty_get_cursor_pos(t_cursor_pos *cursor_pos)
{
    char    buf[32];
    int     read_ret;
    int     i;

    write(STDIN_FILENO, "\x1b[6n", 4);
    if ((read_ret = read(STDIN_FILENO, buf, 32)) <= 0)
        fatal("read error");
    buf[read_ret] = '\0';
    cursor_pos->row = ft_atoi(&buf[2]);
    i = 2;
    while (buf[i] != ';' && buf[i])
        i++;
    if (!buf[i])
        fatal("no cursor column provided");
    cursor_pos->col = ft_atoi(&buf[i + 1]);
}