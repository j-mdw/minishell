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
#define ARROW_UP "\x1b[A"
#define ARROW_DOWN "\x1b[B"

#define READ_BUF_SIZE 4096
#define HIST_SIZE 100
#define SHELL_MSG "coquillage"

typedef struct  s_cursor_pos {
    int start_row;
    int start_col;
    int max_row;
    int max_col;
    int row;
    int col;
}               t_cursor_pos;

typedef struct  s_tty_param {
    t_cursor_pos    *cursor_pos;
    char            **line_hist;
    int             hist_size;
    int             line_index;
}               t_tty_param;

struct termios g_origin_termios;

int     tty_init_cursor_pos(t_cursor_pos *cursor_pos);
int     tty_get_cursor_pos(t_cursor_pos *cursor_pos);
int     tty_echo_del(t_cursor_pos *cursor_pos, char *read_buf);
int     tty_move_left(int n);
int     tty_newline(t_cursor_pos *cursor_pos);
int     tty_set_raw_mode(struct termios *raw_termios);
int     tty_get_line(char **hist, char *newline);
int     get_escape_seq(char *buf);
int     tty_echo_esc(t_tty_param *tty_param);
int     tty_write_over(char *read_buf, char c);
int     tty_error(char *error_msg);
int     tty_read_echo(t_cursor_pos *cursor_pos, char **hist, int hist_size, char *line);
int     tty_echo_char(t_cursor_pos *cursor_pos, char *read_buf, int index, char c);
char    *dynamic_next_line(char **arr, int arr_size, int str_size);
int     dynamic_get_next_free(char **arr, int arr_size);

#endif