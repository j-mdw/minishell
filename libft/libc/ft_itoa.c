/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 07:58:41 by clkuznie          #+#    #+#             */
/*   Updated: 2019/10/21 07:59:19 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrpwr(int n)
{
	int		pwr;

	pwr = 1;
	while (n /= 10)
		pwr *= 10;
	return (pwr);
}

char		*
	ft_itoa(int n)
{
	int		pwr;
	int		len;
	char	*a_nbr;
	int		i;

	pwr = nbrpwr(n);
	len = ft_nbrlen(n) + ((n < 0) ? 1 : 0);
	if (!(a_nbr = malloc(sizeof(*a_nbr) * len + 1)))
		return (NULL);
	i = 0;
	if (n < 0 && (a_nbr[i] = '-'))
		++i;
	while (i < len && (a_nbr[i] = (n / pwr) % 10 * ((n < 0) ? -1 : 1) + '0'))
	{
		pwr /= 10;
		++i;
	}
	a_nbr[i] = '\0';
	return (a_nbr);
}
