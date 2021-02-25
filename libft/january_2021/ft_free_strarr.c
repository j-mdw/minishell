/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strarr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:22:23 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 21:27:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Free string arr data
** Set *strarr to NULL
*/

void
	ft_free_strarr(char ***strarr)
{
	int	i;

	i = 0;
	if (*strarr)
	{
		while ((*strarr)[i])
		{
			free((*strarr)[i]);
			(*strarr)[i] = NULL;
			i++;
		}
		free(*strarr);
		*strarr = NULL;
	}
}
