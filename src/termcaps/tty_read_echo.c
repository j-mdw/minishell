#include "termcaps.h"

static  int
    tty_read_echo_2(t_cursor_pos *cursor_pos, char *read_buf, int row_index, char c)
{
    if (c == 127 && row_index && (tty_echo_del(cursor_pos, read_buf) < 0))
        return (-1);
    else if (c == 3)
    {
        ft_bzero(read_buf, READ_BUF_SIZE);
        write(STDIN_FILENO, "\r\n", 2);
        if (tty_newline(cursor_pos) < 0)
            return (-1);
    }
    else if (c == 4 && !read_buf[0])
        return (-1);
    else if (c == '\r')
        return (1);
    return (0);
}

int
    tty_read_echo(t_cursor_pos *cursor_pos, char **line)
{
    char    *read_buf;
    char    c;
    int     row_index;
    int     ret;

    if (!(*line = (char *)malloc(READ_BUF_SIZE))    )
        return(tty_error("malloc"));
    read_buf = *line;
    ft_bzero(read_buf, READ_BUF_SIZE);
    while (1)
    {
        row_index = cursor_pos->row - cursor_pos->start_row;
        if ((read(STDIN_FILENO, &c, 1)) < 0)
            return(tty_error("read"));
        if (c == '\x1b' && (tty_echo_esc(cursor_pos) < 0))
            return (-1);
        else if (ft_isprint(c) && \
        (tty_echo_char(cursor_pos, read_buf, row_index, c) < 0))
            return (-1);
        else
        {
            if ((ret = tty_read_echo_2(cursor_pos, read_buf, row_index, c)) != 0)
                return (ret);
        }
    }
}