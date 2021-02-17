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
    fatal(char *err_msg)
{
    dprintf(STDERR_FILENO, "Error: %s: %s\n", err_msg, strerror(errno));
    if (tcsetattr(STDIN_FILENO, TCSANOW, &g_origin_termios) < 0)
        dprintf(STDERR_FILENO, "Error: tcsetattr: tty reset failed\n");
    exit(EXIT_FAILURE);
}

void
    tty_set_raw_mode(struct termios *raw_termios)
{
    cfmakeraw(raw_termios);
    // raw_termios->c_lflag &= ~(ICANON | ECHO);
    raw_termios->c_lflag |= ISIG;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, raw_termios) < 0)
        fatal("tcsetattr");
}

void
    get_escape_seq(char *buf)
{
    int     i;

    i = 0;
    buf[0] = '\x1b';
    while (!ft_isalpha(buf[i]))
    {
        i++;
        if (read(STDIN_FILENO, &buf[i], 1) < 0)
            fatal("read");
    }
}

void
    tty_echo_esc(t_cursor_pos *cursor_pos)
{
    char    esc_buf[32];

    ft_bzero(esc_buf, 32);
    get_escape_seq(esc_buf);
    if (!ft_strcmp(esc_buf, ARROW_RIGHT) && (cursor_pos->row < cursor_pos->max_row))
    {
            write(STDIN_FILENO, esc_buf, 3);
            cursor_pos->row++;
    }
    if (!ft_strcmp(esc_buf, ARROW_LEFT) && (cursor_pos->row > (cursor_pos->start_row)))
    {
        cursor_pos->row--;
        write(STDIN_FILENO, esc_buf, 3);
    }
}

void
    tty_echo_rep(char *symbol, int repeat)
{
    int     symbol_len;

    symbol_len = ft_strlen(symbol);
    while (repeat-- > 0)
        write(STDIN_FILENO, symbol, symbol_len);
}

#define READ_BUF_SIZE 4096

void
    tty_read_echo(t_cursor_pos *cursor_pos)
{
    int     read_ret;
    char    read_buf[READ_BUF_SIZE];
    char    c;
    int     i;
    int     row_index;

    i = 0;
    ft_bzero(read_buf, READ_BUF_SIZE);
    while (1)
    {
        row_index = cursor_pos->row - cursor_pos->start_row;
        if ((read_ret = read(STDIN_FILENO, &c, 1)) < 0)
            fatal("read");
        if (c == '\x1b')
            tty_echo_esc(cursor_pos);
        else if (c == 'q')
            break;
        else if (ft_isprint(c))
        {
            if (cursor_pos->row == cursor_pos->max_row)
            {
                write(STDIN_FILENO, &c, 1);
                read_buf[row_index] = c;
            }
            else if (cursor_pos->row < cursor_pos->max_row)
            {
                ft_memmove(&read_buf[row_index + 1], &read_buf[row_index], cursor_pos->max_row - cursor_pos->row + 1);
                read_buf[row_index] = c;
                i = cursor_pos->max_row - cursor_pos->row + 1;
                write(STDIN_FILENO, &read_buf[row_index], i);
                tty_echo_rep(ARROW_LEFT, i - 1);
            }
            cursor_pos->row++;
            cursor_pos->max_row++;
        }

    }
}

int
    main(void)
{
    struct termios  raw_termios;
    t_cursor_pos    cursor_pos;
    char            c;
    int             read_ret;

    if (tcgetattr(STDIN_FILENO, &g_origin_termios) < 0)
        fatal("tcgetattr");
    raw_termios = g_origin_termios;
    tty_set_raw_mode(&raw_termios);
    write(1, "BJ$>", 4);
    tty_init_cursor_pos(&cursor_pos);
    tty_read_echo(&cursor_pos);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_origin_termios);
    return(EXIT_SUCCESS);
}
