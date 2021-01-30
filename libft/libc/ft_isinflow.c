/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinflow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 06:15:46 by clkuznie          #+#    #+#             */
/*   Updated: 2019/12/16 06:15:51 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_isinflow(int current, int next_digit, int sign)
{
	if (ft_nbrlen(current) + 1 == ft_nbrlen(INT_MAX))
	{
		if (current > INT_MAX / 10)
			return (sign > 0 ? -1 : 0);
		if (current == INT_MAX / 10)
		{
			if (next_digit > INT_MAX % 10 + (sign > 0 ? 0 : 1))
				return (sign > 0 ? -1 : 0);
		}
	}
	return (1);
}
