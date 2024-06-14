/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:05:45 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/14 21:59:06 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <string.h>
# include <stdbool.h>

# define FORK_FAILURE	"fork failure\n"
# define PIPE_FAILURE	"pipe failure\n"
# define ARGC_FAILURE	"argc failure\n"
# define IN_FAILURE		"infile failure\n"
# define OUT_FAILURE	"outfile failure\n"
# define PARENT_FAILURE	"parent failure\n"
# define CHILD_FAILURE	"child failure\n"
# define ENV_FAILURE	"environnement failure\n"
# define INIT_SUCCESS	"init succeed\n"

typedef struct s_ctx
{
	int ac;
	char **av;
}	t_ctx;

typedef struct s_cmd
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	char	*path;
	char	**path_split;
	char	**path_comps;
	char	**env;
}	t_cmd;


/* WIP */
void	ft_child(char **argv, t_cmd *cmd);
void	ft_parent(char **argv, t_cmd *cmd);
int		executing(t_ctx *ctx, t_cmd *cmd, char **argv);


/* init*/
char	*init_cmd(t_ctx *ctx, t_cmd *cmd, char **argv);

/* path */
int		get_path(t_cmd *cmd);

/* error */
void	ft_putendl_fd(char *s, int fd);

/* memory */
void	free_tab(void **tab);

/* array */
size_t	ft_strlen(char *s);
char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlcat(char *dest, char *src, size_t size);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
char	*ft_triple_strjoin(char *s1, char *s2, char *s3);
#endif