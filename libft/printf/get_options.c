/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 02:44:55 by clkuznie          #+#    #+#             */
/*   Updated: 2020/07/21 02:45:04 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	flags_init(t_flags *options)
{
	options->length = 0;
	options->prec = -1;
	options->ladjust = 0;
	options->padc = ' ';
	options->plus_sign = 0;
	options->sign_char = 0;
	options->base = 10;
	options->u_print = 0;
	options->caps = 0;
	options->ptr = 0;
	options->altfm = 0;
}

void
	get_flags(const char **fmt, t_flags *options)
{
	flags_init(options);
	while (1)
	{
		if (**fmt == '#')
			options->altfm = 1;
		else if (**fmt == '+')
			options->plus_sign = '+';
		else if (**fmt == '-')
			options->ladjust = 1;
		else if (**fmt == '0')
			options->padc = '0';
		else if (**fmt == ' ')
		{
			if (options->plus_sign == 0)
				options->plus_sign = ' ';
		}
		else
			break ;
		++*fmt;
	}
}

void
	get_length(const char **fmt, t_flags *options, va_list *arg_ptr)
{
	if (ft_isdigit(**fmt))
	{
		while (ft_isdigit(**fmt))
		{
			options->length = 10 * options->length + (**fmt - '0');
			++*fmt;
		}
	}
	else if (**fmt == '*')
	{
		options->length = va_arg(*arg_ptr, int);
		++*fmt;
		if (options->length < 0)
		{
			options->ladjust = 1;
			options->padc = ' ';
			options->length = -options->length;
		}
	}
}

void
	get_precision(const char **fmt, t_flags *options, va_list *arg_ptr)
{
	if (**fmt == '.')
	{
		++*fmt;
		options->prec = 0;
		if (ft_isdigit(**fmt))
		{
			options->prec = 0;
			while (ft_isdigit(**fmt))
			{
				options->prec = 10 * options->prec + (**fmt - '0');
				++*fmt;
			}
		}
		else if (**fmt == '*')
		{
			options->prec = va_arg(*arg_ptr, int);
			++*fmt;
		}
	}
}
