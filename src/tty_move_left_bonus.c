/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_move_left_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:46:37 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 17:07:13 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

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
	return (0);
}
