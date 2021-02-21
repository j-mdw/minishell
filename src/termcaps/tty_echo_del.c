#include "termcaps.h"

int
    tty_echo_del(t_cursor_pos *cursor_pos, char *read_buf)
{
    int col_index;
    int i;

    col_index = cursor_pos->col - cursor_pos->start_col;
    ft_memmove(&read_buf[col_index - 1], &read_buf[col_index], \
    ft_strlen(&read_buf[col_index]));
    read_buf[cursor_pos->max_col - cursor_pos->start_col - 1] = '\0';
    write(STDIN_FILENO, ARROW_LEFT, 3);
    cursor_pos->col--;
    cursor_pos->max_col--;
    i = cursor_pos->max_col - cursor_pos->col;
    write(STDIN_FILENO, &read_buf[col_index - 1], i + 1);
    write(STDIN_FILENO, " ", 1);
    write(STDIN_FILENO, "\x1b[J", 3);
    if (tty_move_left(i + 1) < 0)
        return (-1);
    return (0);
}