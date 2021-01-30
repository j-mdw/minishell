/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power_base_to2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:30:38 by user42            #+#    #+#             */
/*   Updated: 2020/11/13 14:32:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double
g_powersof10[] = {
	10.,
	100.,
	1.0e4,
	1.0e8,
	1.0e16,
	1.0e32,
	1.0e64,
	1.0e128,
	1.0e256,
};

double
	power_base_to2(int exp)
{
	double	dexp;
	double	*power;

	dexp = 1.0;
	power = g_powersof10;
	while (exp != 0)
	{
		if (exp & 01)
			dexp *= *power;
		exp >>= 1;
		power++;
	}
	return (dexp);
}
