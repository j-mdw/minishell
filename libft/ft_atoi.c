/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:25:25 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/19 04:16:46 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_check_sign(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		power;
	double	res;

	power = 0;
	i = 0;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	sign = ft_check_sign(str[0]);
	if (sign == -1)
		str++;
	else if (*str == '+')
		str++;
	while (str[power] <= '9' && str[power] >= '0')
		power++;
	while (i < power)
	{
		res = res * 10 + ((str[i] - 48));
		if ((res * sign) > 2147483647 || (res * sign) < -2147483648)
			return (-1);
		i++;
	}
	return (res * sign);
}
