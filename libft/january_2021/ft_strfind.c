/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:26:35 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 21:34:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_strfind(const char **array, const char *str)
{
	int		i;

	i = 0;
	while (array[i])
	{
		if (!ft_strcmp(array[i], str))
			return (i);
		i++;
	}
	return (-1);
}
