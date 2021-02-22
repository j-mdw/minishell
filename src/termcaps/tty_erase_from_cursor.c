#include "termcaps.h"

void
    tty_erase_from_crusor(t_cursor_pos *cursor_pos)
{
    write(STDIN_FILENO, "\x1b[K", 3);
    cursor_pos->max_col = cursor_pos->col;
    cursor_pos->max_row = cursor_pos->row;
}