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
    - if yes, check if 1st char is '.':
        - if yes, replace it with getpwd and return (NOT VERIFYING IF THE FILE EXISTS)
        - if no, duplicate 'bin' and return
    if no:
        - split path on ':'
        - search each dir using readir (not sure why I'd check file type)
*/

static char
    *direct_path(char *bin)
{
    char    *filename;
    char    *path;
    
    if (bin[0] == '.')
    {
        if (!(path = getcwd(NULL, 0)))
        {
            printf("error: getcwd: %s\n", strerror(errno));
            return (NULL);
        }
        if (!(filename = ft_strjoin(path, bin + 1)))
            printf("error: getcwd: %s\n", strerror(errno));
        free(path);
        return (filename);
    }
    return (ft_strdup(bin));
}

static int
    search_dir(char *dir, char *bin)
{
    DIR             *dirp;
    struct dirent   *dirread;

    if (!(dirp = opendir(dir)))
    {
        printf("error: opendir: %s\n", strerror(errno));
        return (0);
    }
    errno = 0;
    while ((dirread = readdir(dirp)))
        if (!(ft_strcmp(dirread->d_name, bin)))
            return (1);
    if (errno != 0)
        printf("error: readdir: %s\n", strerror(errno));
    if (closedir(dirp) < 0)
        printf("error: closedir: %s\n", strerror(errno));
    return (0);
}

char
    *search_path(char *path, char *bin)
{
    char    **path_split;
    char    *filename;
    char    *filename2;
    int     i;

    if (ft_strchr(bin, '/'))
        return (direct_path(bin));
    if ((!path) || !(path_split = ft_split(path, ':')))
        return (ft_strdup(bin));
    i = 0;
    while (path_split[i])
    {
        if (search_dir(path_split[i], bin))
        {
            if (path_split[i][ft_strlen(path_split[i]) - 1] != '/')
            {
                if (!(filename = ft_strjoin(path_split[i], "/")))
                    printf("error: strjoin: %s\n", strerror(errno));
                ft_free_strarr(&path_split);
            }
            if (!(filename2 = ft_strjoin(filename, bin)))       //Relies on Null string protection of ft_strjoin
                printf("error: strjoin: %s\n", strerror(errno));
            free(filename);
            return (filename2);
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
    char *path = "/bin/";
    char *bin1 = "/ls";
    char *bin2 = "./ls";
    char *bin3 = "ls";
    char *bin4 = "pwd";
    char *bin5 = "//////ls";
    char *bin6 = "//////ls";
    char *bin7 = "/home/user42/ls";
    char *bin8 = "./minishell/src/ls";

    char *name = search_path(path, bin1);
    printf("%s\n", name);
    name = search_path(path, bin2);
    printf("%s\n", name);
    name = search_path(path, bin3);
    printf("%s\n", name);
    name = search_path(path, bin4);
    printf("%s\n", name);
    name = search_path(path, bin5);
    printf("%s\n", name);
    name = search_path(path, bin6);
    printf("%s\n", name);
    name = search_path(path, bin7);
    printf("%s\n", name);
    name = search_path(path, bin8);
    printf("%s\n", name);
    return (0);
}
*/