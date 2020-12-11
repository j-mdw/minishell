/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 03:51:19 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/15 21:16:37 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_find_power(unsigned int n)
{
	int power;

	power = 1;
	while ((n / 10) > 0)
	{
		n /= 10;
		power++;
	}
	return (power);
}

static int	ft_divisor(unsigned int power)
{
	int divisor;

	divisor = 1;
	while (power > 1)
	{
		divisor *= 10;
		power--;
	}
	return (divisor);
}

static char	*ft_setstr(unsigned int n, int power, int sign)
{
	char	*ptr;
	int		i;
	int		divisor;

	ptr = (char *)malloc(sizeof(char) * (power + sign + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[power + sign] = '\0';
	i = 0;
	if (sign == 1)
	{
		ptr[i] = '-';
		i++;
	}
	divisor = ft_divisor(power);
	while (divisor > 0)
	{
		ptr[i] = (n / divisor) + 48;
		i++;
		n = n % divisor;
		divisor /= 10;
	}
	return (ptr);
}

char		*ft_itoa(int n)
{
	int				power;
	int				sign;
	char			*ptr;
	unsigned int	n1;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n1 = n * -1;
	}
	else
		n1 = n;
	power = ft_find_power(n1);
	ptr = ft_setstr(n1, power, sign);
	return (ptr);
}
