/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:22:42 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/13 23:27:00 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/errno.h>

char	*ft_strdup(const char *s1)
{
	int		len_s1;
	int		i;
	char	*sd;

	len_s1 = 0;
	while (s1[len_s1] != '\0')
		len_s1++;
	sd = (char *)malloc(sizeof(char) * (len_s1 + 1));
	if (sd == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (i < len_s1)
	{
		sd[i] = s1[i];
		i++;
	}
	sd[i] = '\0';
	return (sd);
}
