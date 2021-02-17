/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:42:27 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 16:03:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

char	get_env_toto()
{
	return ('|');
}

char	*param_expand(char *raw_param, char *final_param, int total_len)
{
	int			i;

	i = 0;
	if (raw_param[i] == '$')
	{
		i++;
		while (ft_is_alnum(raw_param[i]) || raw_param[i] == '_')
			i++;
		printf("%c\n", get_env_toto());
	}
	else
	{
		while (raw_param[i] && raw_param[i] != '$')
			i++;
	}
	if (!raw_param[i])
	{
		if (!(final_param = malloc(total_len + 1)))
			printf("Malloc error\n");
		final_param[total_len] = '\0';
		while (i >= 0)
		{
			final_param[total_len] = raw_param[i];
			total_len--;
			raw_param--;
		}
	}
	else
		param_expand(&raw_param[i], )
}

/*
** Move all the characters  within a string by one to the left
** The first character gets discarded and the last char is replaced by a
** a null terminating char '\0'
** INPUT: address of the string to shift
** OUTPUT: nothing
*/
void	*strshift_one_left(char *str)
{
	int				i;
	
	i = 0;
	if (!str || !str[0])
		return ;
	while (str[i++])
		str[i - 1] = str[i];
}

char	*param_trim(char *raw_param)
{
	int				i;
	t_lit_status	lit_status;

	i = 0;
	lit_status_init(&lit_status);
	// if (raw_param[0] == '"' || raw_param[0] == '\'');
	while (raw_param[i])
	{
		if (!(!is_lit(raw_param[i], &lit_status) && raw_param[i] == '$'))
			continue ;
	}
}
