/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_move_cursor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:45:53 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 13:49:52 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

int
	tty_move_cursor(int row, int col, t_cursor *cursor)
{
	char	*row_s;
	char	*col_s;

	if (!(row_s = ft_itoa(row)))
		return (-1);
	if (!(col_s = ft_itoa(col)))
	{
		free(row_s);
		return (-1);
	}
	write(STDIN_FILENO, "\x1b[", 2);
	write(STDIN_FILENO, row_s, ft_strlen(row_s));
	write(STDIN_FILENO, ";", 1);
	write(STDIN_FILENO, col_s, ft_strlen(col_s));
	write(STDIN_FILENO, "H", 1);
	free(row_s);
	free(col_s);
	cursor->row = row;
	cursor->col = col;
	return (0);
}
