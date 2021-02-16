/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:32:59 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 15:33:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*get_filename(char *line)
{
	int		i;
    char    *filename;

	while (ft_isblank(*line))
        line++;
    i = 0;
    while (ft_isprint(line[i]) && line[i] != '<' && line[i] != '>' &&line[i] != ' ')      // TBU
        i++;
    if (i == 0)
    {
        printf("Syntax error");
        return (NULL);
    }
    if (!(filename = ft_substr(line, 0, i)))
        return (NULL);
    return (filename);
}