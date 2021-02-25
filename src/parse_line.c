/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 14:54:13 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 14:54:15 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Split line on ';' then on '|'
** Sends the splited output to 'parse_pipe'
** Returns -1 on program error or Exit Status of
** Returns 0 on success, -1 on error
*/

int
	parse_input(char *line, t_builtin *builtin_data)
{
	int		i;
	int		exit_status;
	char	**controlop_split;
	char	**pipe_split;

	if (!(controlop_split = shell_split(line, ';')))
		return (-1);
	i = 0;
	while (controlop_split[i])
	{
		if (!(pipe_split = shell_split(controlop_split[i], '|')))
		{
			ft_free_strarr(&controlop_split);
			return (-1);
		}
		exit_status = exec_pipe(pipe_split, 0, STDIN_FILENO, builtin_data);
		ft_free_strarr(&(pipe_split));
		i++;
	}
	ft_free_strarr(&controlop_split);
	return (exit_status);
}
