/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:03:39 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 14:15:38 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "minishell.h"

# define ARROW_RIGHT "\x1b[C"
# define ARROW_LEFT "\x1b[D"
# define ARROW_UP "\x1b[A"
# define ARROW_DOWN "\x1b[B"
# define MOVE_START "\x1b[H"
# define MOVE_END "\x1b[F"
# define CTRL_RIGHT "\x1b[1;5C"
# define CTRL_LEFT "\x1b[1;5D"
# define HIST_UP 0
# define HIST_DOWN 1

# define READ_BUF_SIZE 4096
# define HIST_SIZE 5

# ifndef SHELL_MSG
#  define SHELL_MSG "coquillage"
# endif

typedef struct	s_cursor {
	int start_row;
	int start_col;
	int max_row;
	int max_col;
	int row;
	int col;
}				t_cursor;

typedef struct	s_tty_param {
	t_cursor		*cursor;
	char			**line_hist;
	int				hist_size;
	int				newline_index;
	int				current_index;
	char			newline_cpy[READ_BUF_SIZE];
}				t_tty_param;

struct termios	g_origin_termios;

int				tty_init_cursor(t_cursor *cursor);
int				tty_get_cursor(t_cursor *cursor);
int				tty_echo_del(t_cursor *cursor, char *read_buf);
int				tty_move_left(int n);
int				tty_newline(t_cursor *cursor);
int				tty_set_raw_mode(struct termios *raw_termios);
int				tty_get_line(char **hist, int hist_size);
int				get_escape_seq(char *buf);
int				tty_echo_esc(t_tty_param *tty_param, char *read_buf);
int				tty_write_over(char *read_buf, char c);
int				tty_error(char *error_msg);
int				tty_read_echo(t_cursor *cursor, char **hist,
				int hist_size);
int				tty_echo_char(t_cursor *cursor, char *read_buf,
				int index, char c);
int				dynamic_next_line(char **arr, int arr_size);
int				tty_move_cursor(int row, int col, t_cursor *cursor);
void			tty_erase_from_crusor(t_cursor *cursor);
int				tty_iter_hist(t_tty_param *tty_param, char *read_buf,
				int direction);
int				tty_get_line(char *hist[], int hist_size);
void			tty_move_next_word(t_cursor *cursor, char *read_buf);
void			tty_move_previous_word(t_cursor *cursor,
				char *read_buf);
int				tty_get_escape_seq(char *buf);

#endif
