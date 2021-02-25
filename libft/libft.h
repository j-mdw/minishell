/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 11:15:10 by clkuznie          #+#    #+#             */
/*   Updated: 2021/02/25 13:49:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdarg.h>

# define BUFSIZE 16
# define BUFFER_SIZE 64

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_follower
{
	char			buf[BUFFER_SIZE];
	int				i;
	int				len;
	int				junk;
	int				doing;
}				t_follower;

typedef struct	s_flags
{
	int		length;
	int		prec;
	int		ladjust;
	char	padc;
	int		plus_sign;
	int		sign_char;
	int		base;
	int		u_print;
	int		caps;
	int		ptr;
	int		altfm;
}				t_flags;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_iswspace(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strnstr(const char *haystack,
	const char *needle, size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strndup(char const *s1, size_t n);
int				ft_isinset(int c, const char *set);
int				ft_nbrlen(int n);
int				ft_isinflow(int current, int next_digit, int sign);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
	void (*del)(void *));

int				get_next_line(int fd, char **line);

int				ft_printf(const char *fmt, ...);
void			get_flags(const char **fmt, t_flags *options);
void			get_length(const char **fmt, t_flags *options,
	va_list *arg_ptr);
void			get_precision(const char **fmt, t_flags *options,
	va_list *arg_ptr);
void			ft_nb_print(va_list *arg_ptr, t_flags *options);
void			ft_c_print(va_list *arg_ptr, t_flags *options);
void			ft_s_print(va_list *arg_ptr, t_flags *options);
void			ft_p_print(va_list *arg_ptr, t_flags *options);
void			ladjust_print(int i, char *buf, t_flags *options);
void			single_print(int c, t_flags *options);
int				do_write(char c, int info);
void			ft_altx_print(va_list *arg_ptr, t_flags *options);
int				fill_nb_buf(va_list *arg_ptr, t_flags *options, char *buf);

double			power_base_to2(int exp);
double			ft_strtod(char *str, char **endptr);

/*
** JANUARY 2021
*/
int				ft_strcmp(const char *s1, const char *s2);
void			ft_strcpy(char *dest, const char *src);
int				ft_strfind(const char **array, const char *str);
void			ft_putstrarr(char **arr);
void			ft_free_strnarr(char **arr, int arr_size);
void			ft_free_strarr(char ***strarr);
void			ft_list_remove_if(t_list **begin_list, void *data_ref,
	void (*free_fct)(void *));
int				ft_isblank(int c);
#endif
