#include "termcaps.h"

int
    tty_echo_char(t_cursor_pos *cursor_pos, char *read_buf, int index, char c)
{
    if (cursor_pos->row == cursor_pos->max_row)
    {
        write(STDIN_FILENO, &c, 1);
        read_buf[index] = c;
    }
    else if (cursor_pos->row < cursor_pos->max_row)
    {
        if (tty_write_over(&read_buf[index], c) < 0)
            return (-1);
    }
    cursor_pos->row++;
    cursor_pos->max_row++;
    return (0);
}