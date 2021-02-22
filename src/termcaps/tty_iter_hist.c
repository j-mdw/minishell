#include "termcaps.h"

static void
    update_cursor_param(t_cursor_pos *cursor_pos, int len)
{
    cursor_pos->col = cursor_pos->start_col + len;
    cursor_pos->max_col = cursor_pos->col;
}


int
    tty_iter_hist(t_tty_param *tty_param, char *read_buf, int direction)
{
    int     index_change;
    int     buf_len;

    if (direction == HIST_DOWN && (tty_param->current_index < tty_param->newline_index))
        index_change = 1;
    else if (direction == HIST_UP && (tty_param->current_index > 0))
        index_change = -1;
    else
        return (0);
    if ((tty_move_cursor(tty_param->cursor_pos->start_row, \
    tty_param->cursor_pos->start_col, tty_param->cursor_pos)) < 0)
        return (-1);
    tty_erase_from_crusor(tty_param->cursor_pos);
    if (tty_param->current_index == tty_param->newline_index)
        ft_strcpy(tty_param->newline_cpy, read_buf);
    tty_param->current_index += index_change;
    ft_bzero(read_buf, READ_BUF_SIZE);
    if (tty_param->current_index == tty_param->newline_index)
        ft_strcpy(read_buf, tty_param->newline_cpy);
    else
        ft_strcpy(read_buf, tty_param->line_hist[tty_param->current_index]);
    buf_len = ft_strlen(read_buf);
    write(STDIN_FILENO, read_buf, buf_len);
    update_cursor_param(tty_param->cursor_pos, buf_len);
    return (0);
}