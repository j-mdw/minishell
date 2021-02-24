/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_erase_from_cursor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:07:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 12:07:16 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void
	tty_erase_from_crusor(t_cursor *cursor)
{
	write(STDIN_FILENO, "\x1b[K", 3);
	cursor->max_col = cursor->col;
	cursor->max_row = cursor->row;
}
