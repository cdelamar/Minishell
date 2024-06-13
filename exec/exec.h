/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:36:14 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/13 16:32:56 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

char	*get_next_line(int fd);
char	*ft_trim_storage(char *storage);
char	*ft_getline(char *storage);
char	*ft_readline(int fd, char *storage);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
size_t	ft_strlen(char *str);

#endif