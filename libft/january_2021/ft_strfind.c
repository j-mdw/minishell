/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 11:30:27 by clkuznie          #+#    #+#             */
/*   Updated: 2021/01/30 11:55:04 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
    ft_strfind(const char **array, const char *str)
{
    int     i;

    i = 0;
    while (array[i])
    {
        if (!ft_strcmp(array[i], str))
            return (i);
        i++;
    }
    return (-1);
}
