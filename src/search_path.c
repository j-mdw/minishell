#include "minishell.h"
/*
** Split path on ':' and search for bin in cucrrent dir
** if bin begind with './' or in directories specified
** by path
** @param path : string of directories to search separated by ':'
** @param : name of the file to search
** @return : if 'bin' found, return mallocated filename (including full path) to bin
** otherwise, if path is NULL, return mallocated copy of bin, otherwise, NULL is returned
*/

/*
- Check if '/' in bin : means me have a full path
    - if yes, return strdup(bin)
    - if no:
        - split path on ':'
        - search each dir using stat, check if file is a regular file, return mallocated filename or NULL
*/


 static char
    *search_path2(char *path, char *bin)
 {
    char    *filename1;
    char    *filename2;
    struct stat statbuf;
    int k;

    if (path[ft_strlen(path) - 1] != '/')
    {
        if (!(filename1 = ft_strjoin(path, "/")))
            printf("error: strjoin: %s\n", strerror(errno));
    }
    else
        filename1 = ft_strdup(path);
    if (!(filename2 = ft_strjoin(filename1, bin)))       //Relies on Null string protection of ft_strjoin
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
    char    **path_split;
    char    *filename;
    int     i;

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
    printf("minishell: command not found: %s\n", bin);
    return (NULL);
}
/*
 gcc search_path.c ../libft/libft.a -I../ -I../libft/
int main(void)
{
    char *path = "/bin";
    char *bin1 = "/ls";
    char *bin2 = "./ls";
    char *bin3 = "ls";
    char *bin4 = "pwd";
    char *bin5 = "//////ls";
    char *bin6 = "//////ls";
    char *bin7 = "/home/user42/ls";
    char *bin8 = "./minishell/src/ls";
    char *bin9 = "ptd";

    char *name = search_path(path, bin1);
    printf("%s\n", name);
    free(name);
    name = search_path(path, bin2);
    printf("%s\n", name);
    free(name);
    name = search_path(path, bin3);
    printf("%s\n", name);
    free(name);
    name = search_path(path, bin4);
    printf("%s\n", name);
    free(name);
    name = search_path(path, bin5);
    printf("%s\n", name);
    free(name);
    name = search_path(path, bin6);
    printf("%s\n", name);
    free(name);
    name = search_path(path, bin7);
    printf("%s\n", name);
    free(name);
    name = search_path(path, bin8);
    printf("%s\n", name);
    free(name);
    name = search_path(path, bin9);
    printf("%s\n", name);
    free(name);
    return (0);
}
*/