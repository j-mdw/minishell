/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_free_data_struct.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:48:38 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 13:48:44 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin_free_data_struct(t_builtin *builtin_data)
{
	ft_free_strnarr(builtin_data->builtin_names_arr, BUILTIN_COUNT);
	ft_lstclear(&(builtin_data->local_env), free);
}
