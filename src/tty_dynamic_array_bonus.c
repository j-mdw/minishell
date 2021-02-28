/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_dynamic_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:05:25 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 12:05:52 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static void
	dynamic_overwrite_first(char **arr, int arr_size)
{
	int i;

	free(arr[0]);
	i = 0;
	while (i < arr_size - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[i] = NULL;
}

static int
	dynamic_get_next_free(char **arr, int arr_size)
{
	int index;

	index = 0;
	while (index < arr_size && arr[index])
		index++;
	if (index == arr_size)
		return (-1);
	return (index);
}

int
	dynamic_next_line(char **arr, int arr_size)
{
	int index;

	if ((index = dynamic_get_next_free(arr, arr_size)) < 0)
	{
		dynamic_overwrite_first(arr, arr_size);
		return (arr_size - 1);
	}
	return (index);
}
