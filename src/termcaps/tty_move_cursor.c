#include "termcaps.h"

int
    tty_move_cursor(int row, int col, t_cursor_pos *cursor_pos)
{

    char    *row_s;
    char    *col_s;

    if (!(row_s = ft_itoa(row)))
        return (-1);
    if (!(col_s = ft_itoa(col)))
    {
        free(row_s);
        return (-1);
    }
    write(STDIN_FILENO, "\x1b[", 2);
    write(STDIN_FILENO,row_s, ft_strlen(row_s));
    write(STDIN_FILENO, ";", 1);
    write(STDIN_FILENO, col_s, ft_strlen(col_s));    
    write(STDIN_FILENO, "H", 1);
    free(row_s);
    free(col_s);
    cursor_pos->row = row;
    cursor_pos->col = col;
    return (0);  
}