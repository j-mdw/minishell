#include "termcaps.h"

void
    tty_move_next_word(t_cursor *cursor, char *read_buf)
{
    int     cursor_i;
    int     max_i;

    cursor_i = cursor->col - cursor->start_col;
    max_i = cursor->max_col - cursor->start_col;
    while (cursor_i < max_i && !ft_isblank(read_buf[cursor_i]))
        cursor_i++;
    while (cursor_i < max_i && ft_isblank(read_buf[cursor_i]))
        cursor_i++;
    // if (cursor_i != max_i)
    //     cursor_i++;
    tty_move_cursor(cursor->row, cursor->start_col + cursor_i, \
    cursor);
}

void
    tty_move_previous_word(t_cursor *cursor, char *read_buf)
{
    int     cursor_i;

    cursor_i = cursor->col - cursor->start_col;
    if (cursor_i > 0)
        cursor_i--;
    while (cursor_i > 0 && ft_isblank(read_buf[cursor_i]))
        cursor_i--;
    while (cursor_i > 0 && !ft_isblank(read_buf[cursor_i]))
        cursor_i--;
    if (cursor_i != 0)
        cursor_i++;
    tty_move_cursor(cursor->row, cursor->start_col + cursor_i, \
    cursor);
}