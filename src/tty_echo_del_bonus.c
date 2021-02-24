/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_echo_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:06:50 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 12:06:52 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int
	tty_echo_del(t_cursor *cursor, char *read_buf)
{
	int col_index;
	int i;

	col_index = cursor->col - cursor->start_col;
	ft_memmove(&read_buf[col_index - 1], &read_buf[col_index], \
	ft_strlen(&read_buf[col_index]));
	read_buf[cursor->max_col - cursor->start_col - 1] = '\0';
	write(STDIN_FILENO, ARROW_LEFT, 3);
	cursor->col--;
	cursor->max_col--;
	i = cursor->max_col - cursor->col;
	write(STDIN_FILENO, &read_buf[col_index - 1], i + 1);
	write(STDIN_FILENO, " ", 1);
	write(STDIN_FILENO, "\x1b[J", 3);
	if (tty_move_left(i + 1) < 0)
		return (-1);
	return (0);
}
