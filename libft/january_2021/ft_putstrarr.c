/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrarr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:25:05 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 12:25:07 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	ft_putstrarr(char **arr)
{
	int i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			ft_putstr_fd(arr[i], STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
	}
}
