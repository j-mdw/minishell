/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 builtin_exit.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: jmaydew <jmaydew@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/02/12 10:16:12 by jmaydew		   #+#	  #+#			  */
/*	 Updated: 2021/02/12 10:16:13 by jmaydew		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

int
	builtin_exit(char **cmd, t_list **env)
{
	(void)cmd;
	(void)env;
	close(STDIN_FILENO);
	return (EXIT_SUCCESS);
}
