/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:42:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/22 15:13:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	**remove_empty_param(char **params)
{
	int		i;
	int		j;

	i = 0;
	while (params[i])
	{
		if (!params[i][0])
		{
			j = i;
			free(params[i]);
			while (params[j++])
				params[j - 1] = params[j];
		}
		i++;
	}
	// if (params[0]) TODO see if anything remains
		return (params);
	// return (NULL);
}

char
	**parse_argv(char *cmd_line, t_list *local_env)
{
	char	**params;
	char 	*trimmed_param;
	int		i;

// check if the programm leaks if shell_split returns a pointer to a NULL pointer
// DO THE EMPTY EXPANSION SHIT
	params = shell_split(cmd_line, ' ');
	i = 0;
	while (params[i])
	{
		if ((trimmed_param = param_trim(params[i], local_env)))
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
			return (params);
		}
		i++;
	}
	return (remove_empty_param(params));
}
