/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 04:43:20 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/14 05:05:34 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_find_power(int n)
{
	int power;

	power = 0;
	while (n > 0)
	{
		n /= 10;
		power++;
	}
	return (power);
}

static int	ft_mybs(int power)
{
	int i;

	i = 1;
	while (power > 1)
	{
		i *= 10;
		power--;
	}
	return (i);
}

void		ft_putnbr_fd(int n, int fd)
{
	int power;
	int i;
	int digit;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		power = ft_find_power(n);
		i = ft_mybs(power);
		while (i > 0)
		{
			digit = (n / i) + 48;
			write(fd, &digit, 1);
			n = n % i;
			i /= 10;
		}
	}
}
