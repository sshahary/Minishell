/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:13:43 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/12 22:51:25 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

int		ft_atoi(const char *str);
void	*ft_bzero(void *ptr, size_t n);
void	*ft_calloc(size_t nitems, size_t size);
char	*ft_itoa(int n);
int		ft_isalnum(int n);
int		ft_isalpha(int n);
int		ft_isascii(int n);
int		ft_isdigit(int n);
int		ft_isprint(int n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
void	*ft_memcpy(void *str1, const void *str2, size_t n);
void	*ft_memmove(void *str1, const void *str2, size_t n);
void	*ft_memset(void *ptr, int x, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(const char*s, char c);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *str1, const char *str2, size_t n);
size_t	ft_strlcpy(char *str1, const char *str2, size_t n);
int		ft_strlen(const char *s);
char	*ft_strmapi(char *const s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strnstr(const char *str1, const char *str2, size_t n);
char	*ft_strrchr(const char *str, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int n);
int		ft_toupper(int n);
int		ft_isspace(const char c);
int		ft_strcmp(const char *s1, const char *s2);
int		int_strchr(char *str, char c);

typedef struct s_lst
{
	void			*content;
	struct s_lst	*next;
}	t_lst;

int		ft_lstsize(t_lst *lst);
t_lst	*ft_lstnew(void *content);
void	ft_lstadd_back(t_lst **lst, t_lst *new);
void	ft_lstadd_front(t_lst **lst, t_lst *new);
t_lst	*ft_lstlast(t_lst *lst);
void	ft_lstdelone(t_lst *lst, void (*del)(void *));
void	ft_lstclear(t_lst **lst, void (*del)(void *));
void	ft_lstiter(t_lst *lst, void (*f)(void *));
t_lst	*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void *));

#endif
