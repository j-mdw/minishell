/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:53:22 by clkuznie          #+#    #+#             */
/*   Updated: 2019/10/15 07:04:38 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		total;
	int		flow_err;

	sign = 1;
	total = 0;
	while (ft_iswspace(*str))
		++str;
	if ((*str == '-' && (sign = -1)) || *str == '+')
		++str;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		if ((flow_err = ft_isinflow(total, str[i] - '0', sign)) != 1)
			return (flow_err);
		total *= 10;
		total += str[i] - '0';
		i++;
	}
	return (total * sign);
}
