/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strarr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:22:23 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 12:22:26 by jmaydew          ###   ########.fr       */
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
	while ((*strarr)[i])
	{
		free((*strarr)[i]);
		(*strarr)[i] = NULL;
		i++;
	}
	free(*strarr);
	*strarr = NULL;
}
