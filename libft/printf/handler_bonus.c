/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 09:58:32 by clkuznie          #+#    #+#             */
/*   Updated: 2020/07/29 09:58:36 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	ft_altx_print(va_list *arg_ptr, t_flags *options)
{
	char			buf[BUFSIZE];
	int				i;
	int				dig_len;

	i = fill_nb_buf(arg_ptr, options, buf);
	if (i == BUFSIZE - 2 && buf[BUFSIZE - 1] == '0')
		options->altfm = 0;
	if (options->prec == 0 && (options->padc = ' ')
		&& i == BUFSIZE - 2 && buf[BUFSIZE - 1] == '0')
		i++;
	if (options->prec > 0 || options->ladjust)
		options->padc = ' ';
	dig_len = (BUFSIZE - 1 - i) + (options->altfm ? 2 : 0);
	options->prec = ((BUFSIZE - 1 - i) > options->prec ?
		0 : options->prec - (BUFSIZE - 1 - i));
	options->length -= dig_len + options->prec;
	while (!options->ladjust && options->padc != '0' && options->length-- > 0)
		do_write(' ', 0);
	if (options->altfm)
	{
		do_write('0', 0);
		do_write((options->caps ? 'X' : 'x'), 0);
	}
	ladjust_print(i, buf, options);
}
