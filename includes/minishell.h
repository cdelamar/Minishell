/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:05:45 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/02 16:26:52 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <linux/limits.h>
# include <readline/readline.h>

# define INIT_SUCCESS	"init succeed\n"
# define FORK_FAILURE	"fork failure\n"
# define PIPE_FAILURE	"pipe failure\n"
# define ARGC_FAILURE	"argc failure\n"
# define CHILD_FAILURE	"child failure\n"
# define IN_FAILURE		"infile failure\n"
# define PARENT_FAILURE	"parent failure\n"
# define MALLOC_FAILURE	"malloc failure\n"
# define OUT_FAILURE	"outfile failure\n"
# define ENV_FAILURE	"environnement failure\n"

// TEST
# define EXIT_COMMAND	3


// PARSING PART

enum token_type {
	WORD, // commands
	OPERATOR, // | < >
	APPEND, // truncate
	HEREDOC, // TODO exec
	VAR, // $[NAME]
	ENV,
	REDIRECT, // <<
	DOUBLE_QUOTE
};

typedef struct s_token {
	enum token_type type;
	char *value;
	struct s_token *next;
} t_token;
// EXECUTING
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
	int		fd_in;
	int		status;
	int		infile;
	int		outfile;
	char	*path;
	char	**path_split;
	char	**path_command;
	char	**env;
}	t_cmd;

// excecuting
int execute (char *line, t_cmd *cmd);
int pipe_execute(char *line, t_cmd *cmd);
int basic_execute (char *line, t_cmd *cmd);

// lexer / tokenizer
enum token_type lexer (char *value);
t_token *tokenizer(char *line);
t_token *create_token (char *value, enum token_type);

// memory
int malloc_structs(t_cmd **cmd, t_ctx **ctx, t_token **token);
void free_structs(t_cmd *cmd, t_ctx *ctx, t_token *token);
void ft_freetab (char **tab);

// command
char *cmd_cat(const char *path_split, char *slash, char *command);
char *cmd_finder(char **split_line, t_cmd *cmd);

// envp
char	*path_finder(t_cmd *cmd, char *path, int size);
void	ft_path(t_cmd *cmd);

// builtins
int ft_builtin(char *line, t_cmd *cmd);
int ft_echo (char **split_line, t_cmd *cmd);
int ft_unset (char **split_line, t_cmd *cmd);
int ft_env(t_cmd *cmd);
int ft_pwd (void);

#endif