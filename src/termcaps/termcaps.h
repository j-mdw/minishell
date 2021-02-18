#ifndef TERMCAPS_H
# define TERMCAPS_H

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libft.h"

#define ARROW_RIGHT "\x1b[C"
#define ARROW_LEFT "\x1b[D"

#define READ_BUF_SIZE 4096
#define SHELL_MSG "coquillage"

typedef struct  s_cursor_pos {
    int start_row;
    int start_col;
    int max_row;
    int max_col;
    int row;
    int col;
}               t_cursor_pos;

struct termios g_origin_termios;

void    tty_init_cursor_pos(t_cursor_pos *cursor_pos);
void    tty_get_cursor_pos(t_cursor_pos *cursor_pos);
void    fatal(char *err_msg);
void    tty_echo_del(t_cursor_pos *cursor_pos, char *read_buf);
void    tty_move_left(int n);
void    tty_newline(t_cursor_pos *cursor_pos);
int     tty_set_raw_mode(struct termios *raw_termios);
int     *tty_get_line(char **line);


void    get_escape_seq(char *buf);
void    tty_echo_esc(t_cursor_pos *cursor_pos);
void    tty_write_over(char *read_buf, char c);

#endif