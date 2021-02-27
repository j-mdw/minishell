/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:22:28 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/27 16:22:32 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	check_var(char *var, t_list **env)
{
	int i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		printf("minishell : unset : '%s' : not a valid identifier\n", var);
		return (-1);
	}
	i = 1;
	while (var[i])
	{
		if (!(ft_isalnum(var[i])) && (var[i] != '_'))
		{
			printf("minishell :unset : '%s' : \
not a valid identifier\n", var);
			return (-1);
		}
		i++;
	}
	ft_list_remove_if(env, var, free);
	return (0);
}

int
	builtin_unset(char **av, t_list **env)
{
	int i;
	int ret;

	if (!av[1])
		return (EXIT_SUCCESS);
	ret = 0;
	i = 1;
	while (av[i])
	{
		ret += check_var(av[i], env);
		i++;
	}
	if (ret == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
