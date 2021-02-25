/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:26:35 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 12:26:38 by jmaydew          ###   ########.fr       */
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
