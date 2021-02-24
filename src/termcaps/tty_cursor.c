/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:04:20 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 12:04:49 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int
	tty_get_cursor(t_cursor *cursor)
{
	char	buf[32];
	int		read_ret;
	int		i;

	write(STDIN_FILENO, "\x1b[6n", 4);
	if ((read_ret = read(STDIN_FILENO, buf, 32)) <= 0)
		return (tty_error("read error"));
	buf[read_ret] = '\0';
	cursor->row = ft_atoi(&buf[2]);
	i = 2;
	while (buf[i] != ';' && buf[i])
		i++;
	if (!buf[i])
	{
		dprintf(STDERR_FILENO, "no cursor column provided");
		return (-1);
	}
	cursor->col = ft_atoi(&buf[i + 1]);
	return (0);
}

int
	tty_init_cursor(t_cursor *cursor)
{
	if (tty_get_cursor(cursor) < 0)
		return (-1);
	cursor->start_col = cursor->col;
	cursor->start_row = cursor->row;
	cursor->max_col = cursor->col;
	cursor->max_row = cursor->row;
	return (0);
}
