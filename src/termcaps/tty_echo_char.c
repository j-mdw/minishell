/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_echo_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:06:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 12:06:19 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int
	tty_echo_char(t_cursor *cursor, char *read_buf, int index, char c)
{
	if (cursor->col == cursor->max_col)
	{
		write(STDIN_FILENO, &c, 1);
		read_buf[index] = c;
	}
	else if (cursor->col < cursor->max_col)
	{
		if (tty_write_over(&read_buf[index], c) < 0)
			return (-1);
	}
	cursor->col++;
	cursor->max_col++;
	return (0);
}
