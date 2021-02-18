#include "termcaps.h"

int
    tty_echo_del(t_cursor_pos *cursor_pos, char *read_buf)
{
    int row_index;
    int i;

    row_index = cursor_pos->row - cursor_pos->start_row;
    ft_memmove(&read_buf[row_index - 1], &read_buf[row_index], \
    ft_strlen(&read_buf[row_index]));
    read_buf[cursor_pos->max_row - cursor_pos->start_row - 1] = '\0';
    write(STDIN_FILENO, ARROW_LEFT, 3);
    cursor_pos->row--;
    cursor_pos->max_row--;
    i = cursor_pos->max_row - cursor_pos->row;
    write(STDIN_FILENO, &read_buf[row_index - 1], i + 1);
    write(STDIN_FILENO, " ", 1);
    write(STDIN_FILENO, "\x1b[J", 3);
    if (tty_move_left(i + 1) < 0)
        return (-1);
    return (0);
}