#include "termcaps.h"

void
    get_escape_seq(char *buf)
{
    int     i;

    buf[0] = '\x1b';
    i = 1;
    if (read(STDIN_FILENO, &buf[i], 1) < 0)
        fatal("read");
    if (buf[i] == '[')
    {
        while (!ft_isalpha(buf[i]))
        {
            i++;
            if (read(STDIN_FILENO, &buf[i], 1) < 0)
                fatal("read");
        }
    }
}

void
    tty_echo_esc(t_cursor_pos *cursor_pos)
{
    char    esc_buf[32];

    ft_bzero(esc_buf, 32);
    get_escape_seq(esc_buf);
    if (!ft_strcmp(esc_buf, ARROW_RIGHT) && (cursor_pos->row < \
    cursor_pos->max_row))
    {
            write(STDIN_FILENO, esc_buf, 3);
            cursor_pos->row++;
    }
    if (!ft_strcmp(esc_buf, ARROW_LEFT) && (cursor_pos->row > \
    (cursor_pos->start_row)))
    {
        cursor_pos->row--;
        write(STDIN_FILENO, esc_buf, 3);
    }
}