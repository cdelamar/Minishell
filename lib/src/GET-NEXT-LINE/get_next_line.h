/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:28:04 by laubry            #+#    #+#             */
/*   Updated: 2023/11/23 17:35:18 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int		ft_strlen_char(char *src, char c);
char	*ft_strjoin_and_free_s1_2(char *s1, char *dest);
char	*ft_strjoin_and_free_s1(char *s1, char *buffer);
int		ft_chr_line(char *buffer);
void	ft_cut_buff(char *buffer);
char	*get_next_line(int fd);

#endif
