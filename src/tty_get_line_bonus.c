/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_get_line_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:41:04 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 17:06:49 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

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
	ret = tty_read_echo(&cursor, hist, hist_size);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_origin_termios) < 0)
		return (tty_error("tty reset failed"));
	return (ret);
}
