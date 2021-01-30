/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 09:52:48 by clkuznie          #+#    #+#             */
/*   Updated: 2020/07/29 09:52:51 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	do_write(char c, int info)
{
	static int	printed_length;

	if (info == 1)
		return (printed_length);
	else if (info == 2 && (printed_length = 0) == 0)
		return (0);
	write(1, &c, 1);
	printed_length++;
	return (printed_length);
}

void
	ladjust_print(int i, char *buf, t_flags *options)
{
	while (options->prec-- > 0
		|| (options->padc == '0' && options->length-- > 0))
		do_write('0', 0);
	while (++i <= BUFSIZE - 1)
		do_write(buf[i], 0);
	while (options->ladjust && options->length-- > 0)
		do_write(' ', 0);
}
