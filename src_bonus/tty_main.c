/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:45:31 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 14:23:48 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int
	main(void)
{
	char	*hist[HIST_SIZE];
	int		ret;
	int		i;

	i = 0;
	while (i < HIST_SIZE)
	{
		hist[i] = NULL;
		i++;
	}
	i = 0;
	while ((ret = tty_get_line(hist, HIST_SIZE)) >= 0)
	{
		(void)ret;
	}
	i = 0;
	while (hist[i])
	{
		printf("\n%s\n", hist[i]);
		free(hist[i]);
		i++;
	}
	return (0);
}
