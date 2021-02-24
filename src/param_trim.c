/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:42:27 by user42            #+#    #+#             */
/*   Updated: 2021/02/24 16:12:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_exp_utils
{
	t_lit_status	*lit_status;
	t_list			*local_env;
	char			*exit_status;
	char 			*raw_param;
	char			*final_param;
	int				char_is_lit;
	char			quote_type;
}				t_exp_utils;


static int
	dollar_expansion(t_exp_utils *utils, char **value_str)
{
	char		*sub_param;
	int			i;

	i = 0;
	sub_param = (utils->raw_param)++;
	while (!utils->char_is_lit && (ft_isalnum(*utils->raw_param) || *utils->raw_param == '_'))
		(utils->raw_param)++;
	if (utils->raw_param != sub_param + 1)
	{
		sub_param = ft_strndup(sub_param + 1, utils->raw_param - sub_param);
		*value_str = env_get_val(utils->local_env, sub_param);
		free(sub_param);
	}
	else if (utils->char_is_lit || *utils->raw_param != '?')
		*value_str = "$";
	else
	{
		*value_str = utils->exit_status;
		utils->raw_param++;
	}
	if (*value_str)
		i = ft_strlen(*value_str);
	return (i);
}

static char		*
	part_write(t_exp_utils *utils, char *value_str, int i)
{
	if (!utils->final_param)
		return (NULL);
	while (i-- > 0)
	{
		utils->final_param--;
		utils->raw_param--;
		if (!value_str)
			*utils->final_param = *utils->raw_param;
		else
			*utils->final_param = value_str[i];
	}
	return (utils->final_param);
}

static int
	param_expand(t_exp_utils *utils, char **value_str)
{
	int				i;
	
	utils->char_is_lit = is_lit(*utils->raw_param, utils->lit_status);
	if (!*utils->raw_param)
		return (0);
	if (*utils->raw_param == '$')
		return (dollar_expansion(utils, value_str));
	if (*utils->raw_param == '\\' && utils->raw_param++)
	{
		utils->char_is_lit = is_lit(*utils->raw_param, utils->lit_status);
		utils->raw_param++;
		return (1);
	}
	i = 0;
	utils->raw_param++;
	while (*utils->raw_param && (utils->char_is_lit || (*utils->raw_param != '\\' && *utils->raw_param != '"'
		&& *utils->raw_param != '\'' && *utils->raw_param != '$')) && ++i)
		utils->raw_param++;
	return (i);
}

static char		*
	param_segment(t_exp_utils utils, int total_len)
{
	int				i;
	char			*value_str;

	i = 0;
	value_str = NULL;
	if ((*utils.raw_param == '\\' || *utils.raw_param == '"'
			|| *utils.raw_param == '\'' || *utils.raw_param == '$'))
		i = param_expand(&utils, &value_str);
	else
	{
		while (*utils.raw_param && *utils.raw_param != '\\' && *utils.raw_param != '"'
			&& *utils.raw_param != '\'' && *utils.raw_param != '$' && ++i)
			utils.raw_param++;
	}
	if (*utils.raw_param)
		utils.final_param = param_segment(utils, total_len + i);
	else
	{
		if (!(utils.final_param = malloc(total_len + i + 1)))
			return (NULL);
		utils.final_param[total_len + i] = '\0';
		utils.final_param = &utils.final_param[total_len + i];
	}
	return (part_write(&utils, value_str, i));
}

char		*
	param_trim(char *raw_param, t_list *local_env)
{
	char			*final_format;
	t_exp_utils		utils;
	t_lit_status	lit_status;

	if (!raw_param)
		return (NULL);
	lit_status_init(&lit_status);
	utils.raw_param = raw_param;
	utils.char_is_lit = 0;
	utils.final_param = NULL;
	utils.local_env = local_env;
	if (!(utils.exit_status = ft_itoa(g_minishell_exit_status)))
		return (NULL);
	utils.lit_status = &lit_status;
	final_format = param_segment(utils, 0);
	free(utils.exit_status);
	return (final_format);
}
