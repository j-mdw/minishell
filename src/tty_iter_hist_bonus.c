/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_iter_hist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:42:29 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 14:16:52 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static void
	update_cursor_param(t_cursor *cursor, int len)
{
	cursor->col = cursor->start_col + len;
	cursor->max_col = cursor->col;
}

int
	tty_iter_hist(t_tty_param *tty_param, char *read_buf, int direction)
{
	int		index_change;

	if (direction == HIST_DOWN &&
		(tty_param->current_index < tty_param->newline_index))
		index_change = 1;
	else if (direction == HIST_UP && (tty_param->current_index > 0))
		index_change = -1;
	else
		return (0);
	if ((tty_move_cursor(tty_param->cursor->start_row, \
	tty_param->cursor->start_col, tty_param->cursor)) < 0)
		return (-1);
	tty_erase_from_crusor(tty_param->cursor);
	if (tty_param->current_index == tty_param->newline_index)
		ft_strcpy(tty_param->newline_cpy, read_buf);
	tty_param->current_index += index_change;
	ft_bzero(read_buf, READ_BUF_SIZE);
	if (tty_param->current_index == tty_param->newline_index)
		ft_strcpy(read_buf, tty_param->newline_cpy);
	else
		ft_strcpy(read_buf, tty_param->line_hist[tty_param->current_index]);
	write(STDIN_FILENO, read_buf, ft_strlen(read_buf));
	update_cursor_param(tty_param->cursor, ft_strlen(read_buf));
	return (0);
}
