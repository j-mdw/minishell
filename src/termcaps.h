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

#endif