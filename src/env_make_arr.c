/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_make_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:18:37 by user42            #+#    #+#             */
/*   Updated: 2021/02/14 13:18:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**env_make_arr(t_list *local_env_lst)
{
	char	**local_env_arr;
	int		lst_size;
	int		i;

	lst_size = ft_lstsize(local_env_lst);
	if (!(local_env_arr = (char **)malloc(sizeof(char *) * (lst_size + 1))))
		return (NULL);
	i = 0;
	while (i < lst_size)
	{
		local_env_arr[i] = local_env_lst->content;
		local_env_lst = local_env_lst->next;
		i++;
	}
	local_env_arr[i] = NULL;
	return (local_env_arr);
}
