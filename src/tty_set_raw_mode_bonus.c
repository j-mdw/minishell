/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_set_raw_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:58:34 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 13:58:54 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int
	tty_set_raw_mode(struct termios *raw_termios)
{
	cfmakeraw(raw_termios);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, raw_termios) < 0)
		return (tty_error("tcsetattr"));
	return (0);
}
