/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 07:55:28 by clkuznie          #+#    #+#             */
/*   Updated: 2020/07/29 07:55:29 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	altered_xformat(va_list *arg_ptr, t_flags *options)
{
	if (options->altfm)
		ft_altx_print(arg_ptr, options);
	else
		ft_nb_print(arg_ptr, options);
}

void
	printf_switch(const char **fmt, va_list *arg_ptr, t_flags *options)
{
	if (**fmt == 'c')
		single_print(va_arg(*arg_ptr, int), options);
	else if (**fmt == 's')
		ft_s_print(arg_ptr, options);
	else if (**fmt == 'd' || **fmt == 'i')
		ft_nb_print(arg_ptr, options);
	else if (**fmt == '%')
		single_print('%', options);
	else if (**fmt == 'u' && (options->u_print = 1))
		ft_nb_print(arg_ptr, options);
	else if (**fmt == 'x' || (**fmt == 'X' && (options->caps = 16)))
	{
		options->u_print = 1;
		options->base = 16;
		altered_xformat(arg_ptr, options);
	}
	else if (**fmt == 'p')
		ft_p_print(arg_ptr, options);
	else if (**fmt == 'o' && (options->base = 8))
		ft_nb_print(arg_ptr, options);
	else
		return ;
	++*fmt;
}

int
	ft_printf(const char *fmt, ...)
{
	va_list	arg_ptr;
	t_flags	options;

	va_start(arg_ptr, fmt);
	do_write('0', 2);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			get_flags(&fmt, &options);
			get_length(&fmt, &options, &arg_ptr);
			get_precision(&fmt, &options, &arg_ptr);
			printf_switch(&fmt, &arg_ptr, &options);
			continue ;
		}
		do_write(*fmt, 0);
		fmt++;
	}
	va_end(arg_ptr);
	return (do_write(*fmt, 1));
}
