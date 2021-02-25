/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_get_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:41:04 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 13:41:30 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int
	tty_get_line(char *hist[], int hist_size)
{
	struct termios	raw_termios;
	t_cursor		cursor;
	int				ret;

	if (tcgetattr(STDIN_FILENO, &g_origin_termios) < 0)
		return (tty_error("tcgetattr"));
	raw_termios = g_origin_termios;
	if (tty_set_raw_mode(&raw_termios) < 0)
		return (-1);
	if (tty_newline(&cursor) < 0)
		return (-1);
	ret = tty_read_echo(&cursor, hist, HIST_SIZE);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_origin_termios) < 0)
		return (tty_error("tty reset failed"));
	return (ret);
}
