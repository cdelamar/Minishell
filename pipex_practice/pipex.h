/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:05:45 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/13 13:08:36 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <string.h>

# define FORK_FAILURE 	"fork failure\n"
# define PIPE_FAILURE 	"pipe failure\n"
# define ARGC_FAILURE 	"argc failure\n"
# define IN_FAILURE		"infile failure\n"
# define OUT_FAILURE		"outfile failure\n"
# define PARENT_FAILURE	"parent failure\n"
# define CHILD_FAILURE	"child failure\n"

typedef struct s_pipex
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	char	*paths;
	char	**split_paths;
	char	**envp;
	int		cmd_nb;
}	t_pipex;

void	ft_init(int argc, char **argv, char **envp, t_pipex *pipex);
void	ft_perror(char *s);
void	ft_child(char **argv, t_pipex *pipex);
void	ft_parent(char **argv, t_pipex *pipex);
void	ft_path(char **envp, t_pipex *pipex);
char	*ft_triple_strjoin(char *s1, char *s2, char *s3);
char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
size_t	ft_strlen(char *s);
size_t	ft_strlcat(char *dest, char *src, size_t size);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
void	free_tab(void **tab);

#endif


/*

*/