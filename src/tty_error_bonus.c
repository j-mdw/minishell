/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:07:38 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 12:07:40 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int
	tty_error(char *error_msg)
{
	dprintf(STDERR_FILENO, "Error: %s: %s\n", error_msg, strerror(errno));
	return (-1);
}