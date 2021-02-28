/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_get_escape_seq.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:39:46 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 13:40:25 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

/*
** Only gets escape sequences starting with [ and ending with a char
*/

int
	tty_get_escape_seq(char *buf)
{
	int		i;

	buf[0] = '\x1b';
	i = 1;
	if (read(STDIN_FILENO, &buf[i], 1) < 0)
		return (tty_error("read"));
	if (buf[i] == '[')
	{
		while (!ft_isalpha(buf[i]))
		{
			i++;
			if (read(STDIN_FILENO, &buf[i], 1) < 0)
				return (tty_error("read"));
		}
		return (0);
	}
	return (tty_error("Unknown escape sequence"));
}
