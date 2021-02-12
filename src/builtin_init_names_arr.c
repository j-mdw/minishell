/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_init_names_arr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:16:37 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/12 12:05:50 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	**builtin_init_names_arr2(char **arr)
{
	if (!(arr[3] = ft_strdup("env")))
	{
		ft_free_strnarr(arr, 3);
		return (NULL);
	}
	if (!(arr[4] = ft_strdup("cd")))
	{
		ft_free_strnarr(arr, 4);
		return (NULL);
	}
	if (!(arr[5] = ft_strdup("export")))
	{
		ft_free_strnarr(arr, 5);
		return (NULL);
	}
	if (!(arr[6] = ft_strdup("unset")))
	{
		ft_free_strnarr(arr, 6);
		return (NULL);
	}
	arr[7] = NULL;
	return (arr);
}

char
	**builtin_init_names_arr(void)
{
	char **arr;

	if (!(arr = (char **)malloc(sizeof(char *) * BUILTIN_COUNT + 1)))
		return (NULL);
	if (!(arr[0] = ft_strdup("echo")))
	{
		free(arr);
		return (NULL);
	}
	if (!(arr[1] = ft_strdup("exit")))
	{
		ft_free_strnarr(arr, 1);
		return (NULL);
	}
	if (!(arr[2] = ft_strdup("pwd")))
	{
		ft_free_strnarr(arr, 2);
		return (NULL);
	}
	return (builtin_init_names_arr2(arr));
}
