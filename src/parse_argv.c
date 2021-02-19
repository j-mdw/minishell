/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:42:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 16:11:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**parse_argv(char *cmd_line)
{
	char	**params;
	char 	*trimmed_param;
	int		i;

// check if the programm leaks if shell_split returns a pointer to a NULL pointer
	params = shell_split(cmd_line, ' ');
	i = 0;
	while (params[i])
	{
		if ((trimmed_param = param_trim(params[i])))
		{
			free(params[i]);
			params[i] = trimmed_param;
		}
		else
		{
			while (params[i])
				i++;
			ft_free_strnarr(params, i);
			free(params);
			params = NULL;
			break ;
		}
		i++;
	}
	return (params);
}
