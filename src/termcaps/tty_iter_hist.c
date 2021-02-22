#include "termcaps.h"


int
    tty_iter_hist(t_tty_param *tty_param)
{
    if ((tty_move_cursor(tty_param->cursor_pos->start_row, \
    tty_param->cursor_pos->start_col, cursor_pos)) < 0)
        return (-1);
    tty_erase_from_crusor(tty_param->cursor_pos);
}