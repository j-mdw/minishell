/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strnarr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:22:37 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 12:22:39 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	ft_free_strnarr(char **arr, int arr_size)
{
	int i;

	i = 0;
	while (i < arr_size)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}
