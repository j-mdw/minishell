/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 builtin_unset.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: jmaydew <jmaydew@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/02/12 10:16:46 by jmaydew		   #+#	  #+#			  */
/*	 Updated: 2021/02/12 10:16:47 by jmaydew		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

int
	builtin_unset(char **av, t_list **env)
{
	int i;

	if (!av[1])
		return (EXIT_SUCCESS);
	if (!ft_isalpha(av[1][0]) && av[1][0] != '_')
	{
		printf("minishell : unset : '%s' : not a valid identifier\n", av[1]);
		return (EXIT_FAILURE);
	}
	i = 1;
	while (av[1][i])
	{
		if (!(ft_isalnum(av[1][i])) && (av[1][i] != '_'))
		{
			printf("minishell :M export : '%s' : \
			not a valid identifier\n", av[1]);
			return (EXIT_FAILURE);
		}
		i++;
	}
	ft_list_remove_if(env, av[1], free);
	return (EXIT_SUCCESS);
}
