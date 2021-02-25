/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_close_cmd_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:15:32 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/14 14:15:51 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	exec_close_cmd_data(t_cmd_data *cmd_data)
{
	close_if(cmd_data->redirfd[0], STDIN_FILENO);
	close_if(cmd_data->redirfd[1], STDOUT_FILENO);
	if (cmd_data->cmd_split)
		ft_free_strarr(&(cmd_data->cmd_split));
	if (cmd_data->filename)
		free(cmd_data->filename);
	if (cmd_data->env_arr)
		free(cmd_data->env_arr);
	return (0);
}
