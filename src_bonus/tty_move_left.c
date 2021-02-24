/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_move_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:46:37 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 13:46:57 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int
	tty_move_left(int n)
{
	char *rep;

	if (!(rep = ft_itoa(n)))
		return (tty_error("move left: itoa"));
	write(STDIN_FILENO, "\x1b[", 2);
	write(STDIN_FILENO, rep, ft_strlen(rep));
	free(rep);
	write(STDIN_FILENO, "D", 1);
}
