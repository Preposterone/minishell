/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:03:42 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 16:17:41 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <ctype.h>
#include <sys/types.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_isspace(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*
** putstr but writes no more than n characters if n < than length of a string
** returns the actual amount of characters printed
*/
size_t	ft_putstrn_fd(const char *s, int fd, int n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_numlen(int n);

/*
** Searches for str in search, returns index if str found, else -1
*/
int		ft_strstrchr(const char *str, const char **search);

/*
** Same as above, but compares no more than 'upto' bytes, -1 on error
*/
int		ft_strstrchr0(char *searchfor, const char **searchin, int upto);
int		ft_strstrchr1(char *cmp, const char **cmpwith, int cmpchars);

/*
** Copies string s1 to the heap, but no more than n characters
** if n > than length of s1, stops at terminating character
*/
char	*ft_strndup(const char *s1, size_t n);

/*
** Memcmp, but case-agnostic when it comes to alphabet
*/
int		ft_memcmpi(const void *s1, const void *s2, size_t n);

/*
** Putchar but at least n times, returns amount of bytes printed
*/
size_t	ft_putnchar_fd(char c, int fd, int n);

/*
** Putnbr_fd, but returns amount of bytes printed, including '-' if n < 0
*/
int		ft_nputnbr_fd(int n, int fd);

/*
** Returns length of an unsigned int
*/
int		ft_numlenu(unsigned int n);

/*
** Putstr_fd, but reversed
*/
size_t	ft_putstrr_fd(char *s, int fd);

/*
** putnbr_fd but n is unsigned, returns numlen
*/
size_t	ft_putnbru_fd(unsigned int n, int fd);

/*
** Itoa except takes any base as argument
*/
char	*ft_itoa_base(unsigned long n, const char *base);

/*
** Returns length of d, using base
*/
size_t	ft_numlen_base(unsigned long d, const char *base);

/*
** memset except it returns amount of characters copied
*/
size_t	ft_memsetn(void *b, int c, size_t len);

/*
** Itoa except takes unsigned int as an argument
*/
char	*ft_utoa(unsigned int n);

/*
** Sets value via pointer, always returns 1
*/
int		ft_set(bool *sw, bool value);

/*
** ?
*/
void	ft_swap(int *a, int *b);

/*
** Frees dst, returns NULL, for use in return statements.
*/
void	*ft_ptr_free(void *dst);

/*
** Frees dst, returns 1, for use in return statements.
*/
int		ft_bool_free(void *dst);

/*
** Searches for c in s, returns index of found element, -1 if not found
*/
int		ft_strchr_index(const char *s, int c);

/*
** Converts each element of s to numeric values,
** returns array of ints allocated on heap, NULL on error.
** if not every character in the string is a digit, returns NULL.
*/
int		*ft_tointarr(const char *s, int len);

/*
** Wrapper function for ft_tointarr:
** converts chars from sub_chr foudn in s into elements of sub_for_ints
*/
int		*ft_tointarr_substitute(char *s, char *sub_chr, int *int_arr);

/*
** bzero which returns true, for use in if statements
*/
bool	if_bzero(void *s, size_t n);

uint	ft_abs(int x);
int		ft_min(int a, int b);
int		ft_max(int a, int b);
int		ft_tern(bool condition, int iftrue, int iffalse);
int64_t	ft_atoll(char *s);

#endif
