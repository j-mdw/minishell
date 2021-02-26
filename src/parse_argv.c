/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:42:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/26 14:19:39 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	**recon_params(char **params)
{
	char	**empty;

	if (params[0])
		return (params);
	free(params);
	if (!(empty = malloc(2 * sizeof(char *))))
		return (NULL);
	empty[1] = NULL;
	if (!(empty[0] = ft_strdup("")))
	{
		free(empty);
		return (NULL);
	}
	return (empty);
}

static void
	remove_empty_param(char **params, int i)
{
	free(params[i]);
	while (params[i])
	{
		params[i] = params[i + 1];
		i++;
	}
}

static char
	**error_free(char **params, int i)
{
	while (params[i])
		i++;
	ft_free_strnarr(params, i);
	free(params);
	return (NULL);
}

char
	**parse_argv(char *cmd_line, t_list *local_env, int be)
{
	char	**params;
	char	*trimmed_param;
	int		i;

	if (!(params = shell_split(cmd_line, ' ')))
		return (NULL);
	i = 0;
	while (params[i])
	{
		if ((trimmed_param = param_trim(params[i], local_env, &be)))
		{
			free(params[i]);
			params[i] = trimmed_param;
			if (!be && !params[i][0])
			{
				remove_empty_param(params, i);
				continue ;
			}
		}
		else
			return (error_free(params, i));
		i++;
	}
	return (recon_params(params));
}
