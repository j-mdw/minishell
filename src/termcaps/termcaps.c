#include "termcaps.h"

/* Notes:

Gestion curseur:
    - Fleches bas/haut:
        - Navigation dans l'historique: a chaque fois avant d'envoyer une ligne, la sauvegarder dans une liste
        - ctrl + haut / ctrl + bas permettent de se deplacer de haut en bas dans la limite de l'index column de base
    - Fleches cotes: comportement naturel - check position du curseur (pas plus a gauche que 
    la position de base, et pas plus a droite que le dernier char + 1)
    - Edition de ligne: sauvegarder les char en buffer dans l'order dans lequel ils sont recus
    et en cas d'input printable a un index qui contient deja des char, recize l'array, ajouter le char et write
    a partir du nouveau char

*/

void
    clear_buf(char *buf, int n)
{
    ft_bzero(buf, n);
}

void
    fatal(char *err_msg)
{
    dprintf(STDERR_FILENO, "Error: %s: %s\n", err_msg, strerror(errno));
    if (tcsetattr(STDIN_FILENO, TCSANOW, &g_origin_termios) < 0)
        dprintf(STDERR_FILENO, "Error: tcsetattr: tty reset failed\n");
    exit(EXIT_FAILURE);
}

void
    tty_exit(void)
{
    write(STDIN_FILENO, "exit\r\n", 6);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &g_origin_termios) < 0)
        dprintf(STDERR_FILENO, "Error: tcsetattr: tty reset failed\n");
    exit(EXIT_SUCCESS);
}

void
    tty_echo_rep(char *symbol, int repeat)
{
    int     symbol_len;

    symbol_len = ft_strlen(symbol);
    while (repeat-- > 0)
        write(STDIN_FILENO, symbol, symbol_len);
}

char
    *tty_read_echo(t_cursor_pos *cursor_pos)
{
    int     read_ret;
    char    *read_buf;
    char    c;
    int     row_index;

    if (!(read_buf = (char *)malloc(sizeof(READ_BUF_SIZE))))
        fatal("malloc");
    clear_buf(read_buf, READ_BUF_SIZE);
    while (1)
    {
        row_index = cursor_pos->row - cursor_pos->start_row;
        if ((read_ret = read(STDIN_FILENO, &c, 1)) < 0)
            fatal("read");
        if (c == '\x1b')
            tty_echo_esc(cursor_pos);
        else if (ft_isprint(c))
        {
            if (cursor_pos->row == cursor_pos->max_row)
            {
                write(STDIN_FILENO, &c, 1);
                read_buf[row_index] = c;
            }
            else if (cursor_pos->row < cursor_pos->max_row)
                tty_write_over(&read_buf[row_index], c);
            cursor_pos->row++;
            cursor_pos->max_row++;
        }
        else if (c == 127 && row_index)
            tty_echo_del(cursor_pos, read_buf);
        else if (c == 3)
        {
            clear_buf(read_buf, READ_BUF_SIZE);
            write(STDIN_FILENO, "\r\n", 2);
            tty_newline(cursor_pos);
        }
        else if (c == 4 && !read_buf[0])
            tty_exit();
        else if (c == '\r')
            return (read_buf);
    }
}

int
    tty_error(char *error_msg)
{
    dprintf(STDERR_FILENO, "Error: %s: %s\n", error_msg, strerror(errno));
    return (-1);
}

int
    *tty_get_line(char **line)
{
    struct termios  raw_termios;
    t_cursor_pos    cursor_pos;
    char            *line;

    if (tcgetattr(STDIN_FILENO, &g_origin_termios) < 0)
        return(tty_error("tcgetattr"));
    raw_termios = g_origin_termios;
    if (tty_set_raw_mode(&raw_termios) < 0)
        return (-1);
    tty_newline(&cursor_pos);
    *line = tty_read_echo(&cursor_pos);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &g_origin_termios) < 0)
        return (tty_error("tty reset failed"));
    return(0);
}

int
    main(void)
{
    char *line;
    
    while (tty_get_line(&line) >= 0)
        printf("line: %s\n", line);
    return (0);
}