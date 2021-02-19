/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:32:59 by user42            #+#    #+#             */
/*   Updated: 2021/02/19 14:34:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*get_filename(char *line, t_list *local_env)
{
	int		i;
	char	*raw_filename;
	char	*filename;
	char	tmp;

	while (ft_isblank(*line) && *line != '\'' && *line != '"')
		line++;
	i = 0;
	tmp = (*line == '\'') * '\'' + (*line == '"') * '"';
	while (ft_isprint(line[i]) && (line[i] == tmp
		|| (!is_operator(line[i]) && line[i] != ' ')))
	{
		i++;
		tmp = 0;
	}
	raw_filename = ft_substr(line, 0, i);
	filename = param_trim(raw_filename, local_env);
	free(raw_filename);
	return (filename);
}
