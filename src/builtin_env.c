/* ************************************************************************** */
/*										  */
/*							  :::	   ::::::::   */
/*	 builtin_env.c					:+:	 :+:	:+:   */
/*							  +:+ +:+		  +:+	  */
/*	 By: jmaydew <jmaydew@student.42.fr>		+#+  +:+	   +#+		  */
/*						  +#+#+#+#+#+	+#+		  */
/*	 Created: 2021/02/12 10:15:47 by jmaydew		   #+#	  #+#		  */
/*	 Updated: 2021/02/12 10:16:04 by jmaydew		  ###	########.fr		  */
/*										  */
/* ************************************************************************** */

#include "minishell.h"

int
	builtin_env(char **argv, t_list **env)
{
	t_list	*iter;

	(void)argv;
	iter = *env;
	if (!(*env))
		return (EXIT_FAILURE);
	while (iter)
	{
		if (ft_strchr(iter->content, '='))
			printf("%s\n", (char *)iter->content);
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}
