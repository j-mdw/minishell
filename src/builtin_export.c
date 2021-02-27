/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:27:28 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/27 16:18:54 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int
	export_print(t_list *env)
{
	char	*ptr;

	while (env)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		if (!(ptr = ft_strchr(env->content, '=')))
			ft_putstr_fd(env->content, STDOUT_FILENO);
		else
		{
			ptr++;
			write(STDOUT_FILENO, env->content, \
			ptr - (char *)env->content);
			write(STDOUT_FILENO, "\"", 1);
			ft_putstr_fd(env->content + \
			(ptr - (char *)env->content), STDOUT_FILENO);
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		env = env->next;
	}
	return (0);
}

static	int
	check_varname(char *var)
{
	int i;

	i = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		printf("minishell : export : '%s' : \
not a valid identifier\n", var);
		return (-1);
	}
	i = 1;
	while (var[i] != '=' && var[i])
	{
		if (!(ft_isalnum(var[i])) && (var[i] != '_'))
		{
			printf("minishell : export : '%s' : \
not a valid identifier\n", var);
			return (-1);
		}
		i++;
	}
	return (i);
}

/*
** - No arg: print env
** - Arg:
**		- key only:
**			- if key already exists - do nothing
**			- if key doesnt exist - add a new elem, copy key in content
**		- key=value:
**			- if key exists: free it, dup arg1 in content
**			- if key doesn't exist: create new elem, dup arg1 in content
*/

static int
	set_var(char *var, t_list **env)
{
	char	*key;
	t_list	*elem;
	int		index;

	if ((index = check_varname(var)) < 0)
		return (-1);
	if (!(key = ft_strndup(var, index)))
		return (-1);
	if (!(elem = env_get_key(*env, key)))
		ft_lstadd_back(env, ft_lstnew(ft_strdup(var)));
	else
	{
		if (var[index])
		{
			free(elem->content);
			if (!(elem->content = ft_strdup(var)))
				return (-1);
		}
	}
	free(key);
	return (0);
}

int
	builtin_export(char **av, t_list **env)
{
	int		i;
	int		ret;

	if (!av[1])
		return (export_print(*env) + EXIT_SUCCESS);
	ret = 0;
	i = 1;
	while (av[i])
	{
		ret += set_var(av[i], env);
		i++;
	}
	if (ret == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
