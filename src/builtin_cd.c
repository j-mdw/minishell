/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:23:50 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/27 15:08:31 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** No arg
**		- Look for HOME variable
**		   - If it exists and has a =value, chdir to HOME
**		   - Else, print error message and return
** Arg:
**
**		- chdir to arg
**		- If error, print message and return
** chdir returned 0:
**	- Look for OLDPWD - if it exists, free it
**	- Look for PWD - if it exists:
**		- get value, merge with OLDPWD=, set OLDPWD to it
**		- set PWD to strdup(new_path)
*/

static int
	cd_set_envvar(t_list *env)
{
	t_list	*oldpwd;
	t_list	*newpwd;
	char	*ptr;

	if ((oldpwd = env_get_key(env, "OLDPWD")))
	{
		free(oldpwd->content);
		if ((ptr = env_get_val(env, "PWD")))
			oldpwd->content = ft_strjoin("OLDPWD=", ptr);
		else
			oldpwd->content = ft_strdup("OLDPWD");
		if (!(oldpwd->content))
			return (-1);
	}
	if ((newpwd = env_get_key(env, "PWD")))
	{
		free(newpwd->content);
		ptr = getcwd(NULL, 0);
		if (!(newpwd->content = ft_strjoin("PWD=", ptr)))
			return (-1);
	}
	return (EXIT_SUCCESS);
}

static int
	exit_error(char *msg)
{
	printf("Error: cd: %s\n", msg);
	return (EXIT_FAILURE);
}

int
	builtin_cd(char **av, t_list **env)
{
	char	*path;
	int		i;

	i = 0;
	while (av[i])
		i++;
	if (i > 2)
		return (exit_error("too many arguments"));
	(void)env;
	if (i == 1)
	{
		if (!(path = env_get_val(*env, "HOME")))
			return (exit_error("'HOME' undefined"));
	}
	else
		path = av[1];
	if (chdir(path) < 0)
	{
		printf("Error: cd: '%s': no such file or directory\n", av[1]);
		return (EXIT_FAILURE);
	}
	return (cd_set_envvar(*env));
}
