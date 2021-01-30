/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 21:10:47 by clkuznie          #+#    #+#             */
/*   Updated: 2020/07/20 21:10:51 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	single_print(int c, t_flags *options)
{
	if (options->ladjust && --options->length)
	{
		do_write(c, 0);
		while (options->length-- > 0)
			do_write(' ', 0);
	}
	else
	{
		while (options->length-- > 1)
			do_write(options->padc, 0);
		do_write(c, 0);
	}
}

int
	fill_nb_buf(va_list *arg_ptr, t_flags *options, char *buf)
{
	unsigned long	u;
	long			n;
	int				i;
	char			*chars;

	chars = "0123456789abcdef0123456789ABCDEF";
	if ((i = BUFSIZE) && options->u_print)
		n = va_arg(*arg_ptr, unsigned int);
	else if (options->ptr)
		u = va_arg(*arg_ptr, unsigned long);
	else
		n = va_arg(*arg_ptr, int);
	if (!options->ptr && n < 0 && (options->sign_char = '-'))
		u = -n;
	else if (!options->ptr)
	{
		u = n;
		options->sign_char = options->plus_sign;
	}
	if (u == 0)
		buf[--i] = '0';
	while (--i >= 0 && u > 0
		&& (buf[i] = chars[u % options->base + options->caps]))
		u /= options->base;
	return (i);
}

void
	ft_nb_print(va_list *arg_ptr, t_flags *options)
{
	char			buf[BUFSIZE];
	int				i;
	int				dig_len;

	i = fill_nb_buf(arg_ptr, options, buf);
	if (options->prec == 0 && (options->padc = ' ')
		&& i == BUFSIZE - 2 && buf[BUFSIZE - 1] == '0')
		i++;
	if (options->prec > 0 || options->ladjust)
		options->padc = ' ';
	dig_len = (BUFSIZE - 1 - i) + (options->sign_char ? 1 : 0);
	options->prec = ((BUFSIZE - 1 - i) > options->prec ?
		0 : options->prec - (BUFSIZE - 1 - i));
	options->length -= dig_len + options->prec;
	while (!options->ladjust && options->padc != '0' && options->length-- > 0)
		do_write(' ', 0);
	if (options->sign_char)
		do_write(options->sign_char, 0);
	while (options->prec-- > 0
		|| (options->padc == '0' && options->length-- > 0))
		do_write('0', 0);
	while (++i <= BUFSIZE - 1)
		do_write(buf[i], 0);
	while (options->ladjust && options->length-- > 0)
		do_write(' ', 0);
}

void
	ft_p_print(va_list *arg_ptr, t_flags *options)
{
	char			buf[BUFSIZE];
	int				i;

	options->base = 16;
	options->ptr = 1;
	i = fill_nb_buf(arg_ptr, options, buf);
	if (options->prec == 0 && i == BUFSIZE - 2 && buf[BUFSIZE - 1] == '0')
		i++;
	if (options->prec > 0)
		options->padc = ' ';
	options->prec = ((BUFSIZE - 1 - i) > options->prec ?
		0 : options->prec - (BUFSIZE - 1 - i));
	options->length -= (BUFSIZE - 1 - i + 2) + options->prec;
	while (!options->ladjust && options->padc != '0' && options->length-- > 0)
		do_write(' ', 0);
	do_write('0', 0);
	do_write('x', 0);
	ladjust_print(i, buf, options);
}

void
	ft_s_print(va_list *arg_ptr, t_flags *options)
{
	char			*str;
	int				str_len;

	if (options->prec == -1)
		options->prec = 0x7fffffff;
	str = va_arg(*arg_ptr, char *);
	if (str == NULL)
		str = "(null)";
	str_len = ft_strlen(str);
	if (options->prec < str_len && options->prec >= 0)
		str_len = options->prec;
	options->length = options->length > str_len ?
		options->length - str_len + 1 : 1;
	if (!options->ladjust && --options->length)
		single_print(' ', options);
	while (*str && str_len--)
		do_write(*str++, 0);
	if (options->ladjust && --options->length)
		single_print(' ', options);
}
