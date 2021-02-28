/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_echo_escape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:36:14 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 13:38:14 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

int
	tty_echo_esc_2(t_tty_param *tty_param, char *read_buf, char *esc_buf)
{
	t_cursor *cursor;

	cursor = tty_param->cursor;
	if (!ft_strcmp(esc_buf, ARROW_UP) &&
	(tty_iter_hist(tty_param, read_buf, HIST_UP) < 0))
		return (-1);
	if (!ft_strcmp(esc_buf, ARROW_DOWN) &&
	(tty_iter_hist(tty_param, read_buf, HIST_DOWN) < 0))
		return (-1);
	if (!ft_strcmp(esc_buf, MOVE_END) &&
	(tty_move_cursor(cursor->max_row, cursor->max_col, cursor) < 0))
		return (-1);
	if (!ft_strcmp(esc_buf, MOVE_START) &&
	(tty_move_cursor(cursor->start_row, cursor->start_col, cursor) < 0))
		return (-1);
	if (!ft_strcmp(esc_buf, CTRL_RIGHT) && (cursor->col < cursor->max_col))
		tty_move_next_word(tty_param->cursor, read_buf);
	if (!ft_strcmp(esc_buf, CTRL_LEFT) && (cursor->col > cursor->start_col))
		tty_move_previous_word(tty_param->cursor, read_buf);
	return (0);
}

int
	tty_echo_esc(t_tty_param *tty_param, char *read_buf)
{
	char		esc_buf[32];
	t_cursor	*cursor;

	cursor = tty_param->cursor;
	ft_bzero(esc_buf, 32);
	if (tty_get_escape_seq(esc_buf) < 0)
		return (-1);
	if (!ft_strcmp(esc_buf, ARROW_RIGHT) &&
	(cursor->col < cursor->max_col))
	{
		write(STDIN_FILENO, esc_buf, 3);
		cursor->col++;
	}
	if (!ft_strcmp(esc_buf, ARROW_LEFT) &&
	(cursor->col > (cursor->start_col)))
	{
		cursor->col--;
		write(STDIN_FILENO, esc_buf, 3);
	}
	else if (tty_echo_esc_2(tty_param, read_buf, esc_buf) < 0)
		return (-1);
	return (0);
}
