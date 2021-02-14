/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_init_funcarr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:27:44 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/14 13:27:56 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin_init_funcarr(t_binfunc_arr *binfunc_arr)
{
	binfunc_arr[0] = builtin_echo;
	binfunc_arr[1] = builtin_exit;
	binfunc_arr[2] = builtin_pwd;
	binfunc_arr[3] = builtin_env;
	binfunc_arr[4] = builtin_cd;
	binfunc_arr[5] = builtin_export;
	binfunc_arr[6] = builtin_unset;
}
