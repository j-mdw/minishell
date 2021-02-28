/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param_trim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:42:27 by user42            #+#    #+#             */
/*   Updated: 2021/02/28 02:41:14 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	dollar_extended(t_exp_utils *utils, char **value_str)
{
	if (utils->lit_char || !*utils->raw_param
		|| *utils->raw_param == '\\' || *utils->raw_param == '%' ||
		*utils->raw_param == '\'' ||
		((*utils->raw_param == '"' && utils->lit_status->dquote)
		&& *utils->raw_param != '?'))
		*value_str = "$";
	else if (*utils->raw_param == '/')
		*value_str = "$/";
	else if (*utils->raw_param != '?')
		*value_str = "";
	else
		return (0);
	return (1);
}

static int
	dollar_expansion(t_exp_utils *utils, char **value_str)
{
	char		*subparam;

	subparam = (utils->raw_param)++;
	while (!utils->lit_char
		&& (ft_isalnum(*utils->raw_param) || *utils->raw_param == '_'))
		(utils->raw_param)++;
	if (utils->raw_param != subparam + 1)
	{
		subparam = ft_strndup(subparam + 1, utils->raw_param - subparam - 1);
		*value_str = env_get_val(utils->local_env, subparam);
		free(subparam);
	}
	else if (dollar_extended(utils, value_str))
		;
	else if ((*value_str = utils->exit_status))
		utils->raw_param++;
	if (*value_str)
		return (ft_strlen(*value_str));
	return (0);
}

static int
	param_expand(t_exp_utils *utils, char **value_str)
{
	int				i;

	utils->lit_char = is_lit(*utils->raw_param, utils->lit_status);
	if (!*utils->raw_param)
		return (0);
	if (*utils->raw_param == '$')
		return (dollar_expansion(utils, value_str));
	(*utils->be)++;
	if (utils->raw_param++ && *(utils->raw_param - 1) == '\\')
	{
		utils->lit_char = is_lit(*(utils->raw_param - 1), utils->lit_status);
		if (utils->raw_param++ && utils->lit_status->dquote &&
			*(utils->raw_param - 1) != '"' &&
			*(utils->raw_param - 1) != '$' && *(utils->raw_param - 1) != '\\')
			return (2);
		return (1);
	}
	i = *(utils->raw_param - 1) == '\'' && utils->lit_status->dquote;
	while (*utils->raw_param &&
		((*utils->raw_param == '\'' && utils->lit_status->dquote)
		|| (*utils->raw_param != '\'' && utils->lit_status->quote)
		|| ((*utils->raw_param != '\\' && *utils->raw_param != '"'
		&& *utils->raw_param != '\'' && *utils->raw_param != '$'))) && ++i)
		utils->raw_param++;
	return (i);
}

static char
	*param_segment(t_exp_utils utils, int total_len)
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
		while (*utils.raw_param
			&& *utils.raw_param != '\\' && *utils.raw_param != '"'
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

char
	*param_trim(char *raw_param, t_list *local_env, int *be)
{
	char			*final_format;
	t_exp_utils		utils;
	t_lit_status	lit_status;

	if (!raw_param)
		return (NULL);
	lit_status_init(&lit_status);
	utils.raw_param = raw_param;
	utils.lit_char = 0;
	utils.final_param = NULL;
	utils.local_env = local_env;
	utils.be = be;
	*utils.be = 0;
	if (!(utils.exit_status = ft_itoa(g_minishell_exit_status)))
		return (NULL);
	utils.lit_status = &lit_status;
	final_format = param_segment(utils, 0);
	free(utils.exit_status);
	return (final_format);
}
