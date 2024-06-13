/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:36:14 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/13 18:28:20 by cdelamar         ###   ########.fr       */
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

typedef struct s_cmd {
    char **argv;           // Array of arguments
    char *input_file;      // Input redirection file
    char *output_file;     // Output redirection file
    int append;            // Append mode for output redirection (1 if >>, 0 if >)
    struct s_cmd *next;		// Next command in the pipeline
} t_cmd;

typedef struct s_ctx {
	char **envp;
} t_ctx;

typedef struct s_exec {
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	bool	infile_ok;
	bool	outfile_ok;
	int		infile;
	int		outfile;
	char	*paths;
	char	**split_paths;
	int		cmd_nb;
} t_exec;


int		ft_path(t_ctx *s_ctx, t_exec *exec);

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