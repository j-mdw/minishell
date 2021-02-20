/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:42:27 by user42            #+#    #+#             */
/*   Updated: 2021/02/20 16:58:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_exp_utils
{
	int		total_len;
	int		char_is_lit;
	char	quote_type;
}				t_exp_utils;


static int
	dollar_expansion(char **raw_param, char **value_str, t_list *local_env)
{
	char		*sub_param;
	int			i;

	i = 0;
	sub_param = (*raw_param)++;
	while (ft_isalnum(**raw_param) || **raw_param == '_')
		(*raw_param)++;
	if (*raw_param != sub_param + 1)
	{
		sub_param = ft_strndup(sub_param + 1, *raw_param - sub_param);
		*value_str = env_get_val(local_env, sub_param);
		free(sub_param);
	}
	else
		*value_str = "$";
	if (*value_str)
		i = ft_strlen(*value_str);
	return (i);
}

static char		*
	param_expand(char *raw_param, char *final_param, int total_len, t_list *local_env)
{
	int			i;
	char		*value_str;

	i = 0;
	value_str = NULL;
	if (*raw_param == '$')
		i = dollar_expansion(&raw_param, &value_str, local_env);
	else
	{
		while (*raw_param && *raw_param != '$' && ++i)
			raw_param++;
	}
	if (*raw_param)
		final_param = param_expand(raw_param, final_param, total_len + i, local_env);
	else
	{
		if (!(final_param = malloc(total_len + i + 1)))
			printf("Malloc error\n");
		final_param[total_len + i] = '\0';
		final_param = &final_param[total_len + i];
	}
	while (i-- > 0)
	{
		final_param--;
		raw_param--;
		if (!value_str)
			*final_param = *raw_param;
		else
			*final_param = value_str[i];
	}
	return (final_param);
}

char		*
	param_trim(char *raw_param, t_list *local_env)
{
	char		*final_format;

	if (!raw_param)
		return (NULL);
	if (raw_param[0])
		final_format = param_expand(raw_param, NULL, 0, local_env);
	else
		final_format = ft_strdup(raw_param);
	return (final_format);
}
