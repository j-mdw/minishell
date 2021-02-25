/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_close_if.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:06:49 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 16:16:22 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Close_if: close fd specified as arg1
** if it is different from value in arg2
** return 0
*/

int
	close_if(int fd1, int diff)
{
	if (fd1 != diff)
		close(fd1);
	return (0);
}
