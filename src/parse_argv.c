/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:42:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/25 21:45:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	**recon_params(void)
{
	char	**empty;

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
			while (params[j])
			{
				params[j] = params[j + 1];
				j++;
			}
		}
		else
			i++;
	}
	if (params[0])
		return (params);
	if (!(params = recon_params()))
		return (NULL);
	return (params);
}

char
	**parse_argv(char *cmd_line, t_list *local_env)
{
	char	**params;
	char	*trimmed_param;
	int		i;

	if (!(params = shell_split(cmd_line, ' ')))
		return (NULL);
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
			return (NULL);
		}
		i++;
	}
	return (remove_empty_param(params));
}
