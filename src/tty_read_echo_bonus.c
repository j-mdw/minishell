/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_read_echo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:56:39 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 16:25:52 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static	int
	tty_read_echo_2(t_tty_param *tty_param, char *read_buf, int col_i, char c)
{
	if (c == 127 && col_i && (tty_echo_del(tty_param->cursor, read_buf) < 0))
		return (-1);
	else if (c == 3)
	{
		ft_bzero(read_buf, READ_BUF_SIZE);
		write(STDIN_FILENO, "\r\n", 2);
		g_minishell_exit_status = 130;
		if (tty_newline(tty_param->cursor) < 0)
			return (-1);
	}
	else if (c == 4 && !read_buf[0])
		return (-1);
	else if (c == '\r')
	{
		write(STDIN_FILENO, "\r\n", 2);
		return (1);
	}
	return (0);
}

void
	init_tty_param(t_tty_param *tty_param, t_cursor *cursor, char **hist,
	int hist_size)
{
	tty_param->cursor = cursor;
	tty_param->line_hist = hist;
	tty_param->hist_size = hist_size;
	tty_param->newline_index = dynamic_next_line(hist, hist_size);
	tty_param->current_index = tty_param->newline_index;
	ft_bzero(tty_param->newline_cpy, READ_BUF_SIZE);
}

int
	tty_read_echo(t_cursor *cursor, char **hist, int hist_size)
{
	t_tty_param	tty_param;
	char		buf[READ_BUF_SIZE];
	char		c;
	int			col_i;
	int			ret;

	init_tty_param(&tty_param, cursor, hist, hist_size);
	ft_bzero(buf, READ_BUF_SIZE);
	while (1)
	{
		col_i = cursor->col - cursor->start_col;
		if ((read(STDIN_FILENO, &c, 1)) < 0)
			return (tty_error("read"));
		if (c == '\x1b' && (tty_echo_esc(&tty_param, buf) < 0))
			return (-1);
		else if (ft_isprint(c) && (tty_echo_char(cursor, buf, col_i, c) < 0))
			return (-1);
		else if ((ret = tty_read_echo_2(&tty_param, buf, col_i, c)) != 0)
		{
			if (ret == 1 && \
			(tty_param.line_hist[tty_param.newline_index] = ft_strdup(buf)))
				return (tty_param.newline_index);
			return (ret);
		}
	}
}
