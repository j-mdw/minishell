#include "termcaps.h"

/*
** Only gets escape sequences starting with [ and ending with a char
*/
int
    get_escape_seq(char *buf)
{
    int     i;

    buf[0] = '\x1b';
    i = 1;
    if (read(STDIN_FILENO, &buf[i], 1) < 0)
        return(tty_error("read"));
    if (buf[i] == '[')
    {
        while (!ft_isalpha(buf[i]))
        {
            i++;
            if (read(STDIN_FILENO, &buf[i], 1) < 0)
                return(tty_error("read"));
        }
    }
    return (0);
}

int
    tty_move_cursor(int row, int col)
{
    unsigned char row_c;
    unsigned char col_c;

    row_c = row;
    col_c = col;
    write(STDIN_FILENO, "\x1b[Y", 4);
    write(STDIN_FILENO, &row_c, 1);
    write(STDIN_FILENO, &col_c, 1);  
}

// int
//     tty_del_line(t_tty_param *tty_param)
// {
// }

int
    tty_echo_esc(t_tty_param *tty_param)
{
    char    esc_buf[32];
    t_cursor_pos *cursor_pos;

    cursor_pos = tty_param->cursor_pos;

    ft_bzero(esc_buf, 32);
    if (get_escape_seq(esc_buf) < 0)
        return (-1);
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
    if (!ft_strcmp(esc_buf, ARROW_UP) && (cursor_pos->row > \
    (cursor_pos->start_row)))
    {
        tty_move_cursor(cursor_pos->start_row, cursor_pos->start_col);
        // tty_del_line();
        // if ()
        // cursor_pos->row--;
        // write(STDIN_FILENO, esc_buf, 3);
    }
    if (!ft_strcmp(esc_buf, ARROW_DOWN) && (cursor_pos->row > \
    (cursor_pos->start_row)))
    {
        // cursor_pos->row--;
        // write(STDIN_FILENO, esc_buf, 3);
    }
    return (0);
}