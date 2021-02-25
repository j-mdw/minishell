/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_search_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:14:54 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 16:15:28 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Split path on ':' and search for bin in cucrrent dir
** if bin begind with './' or in directories specified
** by path
** @param path : string of directories to search separated by ':'
** @param : name of the file to search
** @return : if 'bin' found, return mallocated filename (including full path
** to bin otherwise, if path is NULL, return mallocated copy of bin, otherwise,
** NULL is returned
*/

static char
	*search_path2(char *path, char *bin)
{
	char			*filename1;
	char			*filename2;
	struct stat		statbuf;
	int				k;

	if (path[ft_strlen(path) - 1] != '/')
	{
		if (!(filename1 = ft_strjoin(path, "/")))
			printf("error: strjoin: %s\n", strerror(errno));
	}
	else
		filename1 = ft_strdup(path);
	if (!(filename2 = ft_strjoin(filename1, bin)))
		printf("error: strjoin: %s\n", strerror(errno));
	free(filename1);
	if ((k = stat(filename2, &statbuf)) == 0)
	{
		if (statbuf.st_mode & __S_IFREG)
			return (filename2);
	}
	free(filename2);
	return (NULL);
}

char
	*search_path(char *path, char *bin)
{
	char	**path_split;
	char	*filename;
	int		i;

	if (ft_strchr(bin, '/'))
	{
		if (!(filename = ft_strdup(bin)))
			printf("error: strdup: %s\n", strerror(errno));
		return (filename);
	}
	if ((!path) || !(path_split = ft_split(path, ':')))
		return (ft_strdup(bin));
	i = 0;
	while (path_split[i])
	{
		if ((filename = search_path2(path_split[i], bin)))
		{
			ft_free_strarr(&path_split);
			return (filename);
		}
		i++;
	}
	ft_free_strarr(&path_split);
	return (NULL);
}
