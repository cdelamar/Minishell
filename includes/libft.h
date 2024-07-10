/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 05:09:06 by clement           #+#    #+#             */
/*   Updated: 2024/06/14 16:04:42 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <stddef.h>
//# include <bsd/string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct  s_point
{
    int           x;
    int           y;
}               t_point;

int					ft_atoi(const char *nptr);
void				ft_bzero(void *s, size_t n);
char				*ft_itoa(int n);

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);

int					ft_tolower(int c);
int					ft_toupper(int c);

char				**ft_split(char const *s, char c);
char				*ft_strtrim(char const *s, char const *set);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(const char *s);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strchr(const char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dest, char *src, size_t size);
size_t				ft_strlen(const char *s);

void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_rev_strncmp(const char *s1, const char *s2, size_t n);
void				ft_binary(int index);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_error_message(char *str);
void				ft_flood_fill(char **tab, t_point size, t_point begin);

int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strcspn(const char *s1, const char *s2);



t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void*),
						void (*del)(void *));

char				*get_next_line(int fd);
char				*ft_trim_storage(char *storage);
char				*ft_getline(char *storage);
char				*ft_readline(int fd, char *storage);

#endif
