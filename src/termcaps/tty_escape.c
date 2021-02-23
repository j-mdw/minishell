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
        return (0);
    }
    return (tty_error("Unknown escape sequence"));
}

void
    tty_move_next_word(t_cursor_pos *cursor_pos, char *read_buf)
{
    int     cursor_i;
    int     max_i;

    cursor_i = cursor_pos->col - cursor_pos->start_col;
    max_i = cursor_pos->max_col - cursor_pos->start_col;
    while (cursor_i < max_i && !ft_isblank(read_buf[cursor_i]))
        cursor_i++;
    while (cursor_i < max_i && ft_isblank(read_buf[cursor_i]))
        cursor_i++;
    // if (cursor_i != max_i)
    //     cursor_i++;
    tty_move_cursor(cursor_pos->row, cursor_pos->start_col + cursor_i, cursor_pos);
}

void
    tty_move_previous_word(t_cursor_pos *cursor_pos, char *read_buf)
{
    int     cursor_i;

    cursor_i = cursor_pos->col - cursor_pos->start_col;
    if (cursor_i > 0)
        cursor_i--;
    while (cursor_i > 0 && ft_isblank(read_buf[cursor_i]))
        cursor_i--;
    while (cursor_i > 0 && !ft_isblank(read_buf[cursor_i]))
        cursor_i--;
    if (cursor_i != 0)
        cursor_i++;
    tty_move_cursor(cursor_pos->row, cursor_pos->start_col + cursor_i, cursor_pos);
}

int
    tty_echo_esc(t_tty_param *tty_param, char *read_buf)
{
    char    esc_buf[32];
    t_cursor_pos *cursor_pos;

    cursor_pos = tty_param->cursor_pos;
    ft_bzero(esc_buf, 32);
    if (get_escape_seq(esc_buf) < 0)
        return (-1);
    if (!ft_strcmp(esc_buf, ARROW_RIGHT) && (cursor_pos->col < \
    cursor_pos->max_col))
    {
            write(STDIN_FILENO, esc_buf, 3);
            cursor_pos->col++;
    }
    if (!ft_strcmp(esc_buf, ARROW_LEFT) && (cursor_pos->col > \
    (cursor_pos->start_col)))
    {
        cursor_pos->col--;
        write(STDIN_FILENO, esc_buf, 3);
    }
    if (!ft_strcmp(esc_buf, ARROW_UP) && (tty_iter_hist(tty_param, read_buf, HIST_UP) < 0))
        return (-1);
    if (!ft_strcmp(esc_buf, ARROW_DOWN) && (cursor_pos->col > \
    (cursor_pos->start_col)) && (tty_iter_hist(tty_param, read_buf, HIST_DOWN) < 0))
        return (-1);
    if (!ft_strcmp(esc_buf, MOVE_END) && 
    (tty_move_cursor(cursor_pos->max_row, cursor_pos->max_col, cursor_pos) < 0))
        return (-1);
    if (!ft_strcmp(esc_buf, MOVE_START) && 
    (tty_move_cursor(cursor_pos->start_row, cursor_pos->start_col, cursor_pos) < 0))
        return (-1);
    if (!ft_strcmp(esc_buf, CTRL_RIGHT) && (cursor_pos->col < cursor_pos->max_col))
        tty_move_next_word(tty_param->cursor_pos, read_buf);
    if (!ft_strcmp(esc_buf, CTRL_LEFT) && (cursor_pos->col > cursor_pos->start_col))
        tty_move_previous_word(tty_param->cursor_pos, read_buf);
        return (0);
}