#include "termcaps.h"

static  int
    tty_read_echo_2(t_tty_param *tty_param, char *read_buf, int row_index, char c)
{
    if (c == 127 && row_index && (tty_echo_del(tty_param->cursor_pos, read_buf) < 0))
        return (-1);
    else if (c == 3)
    {
        ft_bzero(read_buf, READ_BUF_SIZE);
        write(STDIN_FILENO, "\r\n", 2);
        if (tty_newline(tty_param->cursor_pos) < 0)
            return (-1);
    } 
    else if (c == 4 && !read_buf[0])
        return (-1);
    else if (c == '\r')
        return (1);
    return (0);
}

static void
    set_line(char **line, char *read_buf)
{
return;
}
int
    tty_read_echo(t_cursor_pos *cursor_pos, char **hist, int hist_size, char *line)
{
    t_tty_param tty_param;
    char    *read_buf;
    char    c;
    int     row_index;
    int     ret;

    tty_param.cursor_pos = cursor_pos;
    tty_param.line_hist = hist;
    tty_param.hist_size = hist_size;
    tty_param.line_index = dynamic_get_next_free(hist, hist_size);
    read_buf = line;
    while (1)
    {
        row_index = cursor_pos->row - cursor_pos->start_row;
        if ((read(STDIN_FILENO, &c, 1)) < 0)
            return(tty_error("read"));
        if (c == '\x1b' && (tty_echo_esc(&tty_param) < 0))
            return (-1);
        else if (ft_isprint(c) && \
        (tty_echo_char(cursor_pos, read_buf, row_index, c) < 0))
            return (-1);
        else
        {
            if ((ret = tty_read_echo_2(&tty_param, read_buf, row_index, c)) != 0)
            {
                // set_line(line, buffer) = ft_strdup(read_buf);
                return (ret);
            }
        }
    }
}