/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:05:45 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/25 03:49:26 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
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
# include <readline/history.h>
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
# define BUFFER_SIZE	5000

# define HEREDOC_ON		1
# define HEREDOC_OFF	0
# define HEREDOC_TMP_FILE "/tmp/heredoc_tmp"

# define FALSE			0
# define TRUE			1

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define EXIT_COMMAND	3

enum e_token_type
{
	WORD,
	OPERATOR,
	APPEND,
	HEREDOC,
	VAR,
	ENV,
	REDIRECT,
	DOUBLE_QUOTE
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_ctx
{
	int		ac;
	char	**av;
}	t_ctx;

typedef struct s_cmd
{
	int		fd[2];
	int		heredoc_processed;
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
void				initialize_cmd(t_cmd *cmd, char *line);
void				handle_error(char *msg, t_cmd *cmd, int *fd);

int					execute(char *line, t_cmd *cmd);

// lexer / tokenizer 9not needed for now)
enum e_token_type	lexer(char *value);
t_token				*tokenizer(char *line);
t_token				*create_token(char *value, enum e_token_type type);

// memory
int					malloc_structs(t_cmd **cmd, t_ctx **ctx, t_token **token);
void				free_structs(t_cmd *cmd, t_ctx *ctx, t_token *token);
void				ft_freetab(char **tab);

// command
char				*cmd_cat(const char *path_split, char *slash,
						char *command);
char				*cmd_finder(char **split_line, t_cmd *cmd);

// envp
int					ft_copy_envp(char **envp, t_cmd *cmd);
char				*path_finder(t_cmd *cmd, char *path, int size);
void				ft_path(t_cmd *cmd);

// builtins
int					ft_builtin(char *line, t_cmd *cmd);
int					ft_echo(char **split_line);
int					ft_unset(char **split_line, t_cmd *cmd);
int					ft_env(t_cmd *cmd);
int					ft_pwd(void);
int					ft_cd(char *path);
int					ft_export(char **args, t_cmd *cmd);

//signals
void				sigint_handler(int sig);
void				signals(void);

//redirections
int					handle_redirections(char **args, int status, t_cmd *cmd);
int					ft_heredoc_redirect(char *delim);
int					ft_input_redirect(char **args, int i);
int					ft_output_redirect(char **args, int i, int append);
int					ft_heredoc(char *limit);


//fd
void				close_fds(int *fd);
int					backup_fd(int *saved_stdin, int *saved_stdout);
void				restore_fd(int saved_stdin, int saved_stdout);
int					open_file(char *filename, int flags, int mode);
int					open_heredoc_file(void);


//basic executing
int					handle_exit_command(char *line);
int					set_command_path(t_cmd *cmd);
int					basic_child_process(char *line, t_cmd *cmd);
int					basic_parent_process(pid_t pid, char **split_line);
int					basic_execute(char *line, t_cmd *cmd);

//pipe executing
void	handle_pipe_error(t_cmd *cmd, int *fd);
void	handle_fork_error(t_cmd *cmd, int *fd);
void	execute_child_process(t_cmd *cmd, int *fd, int i);
void	init_cmd(t_cmd *cmd, char *line);
int		pipe_execute(char *line, t_cmd *cmd);

//WIP
int handle_path(t_cmd *cmd);

// int fork_execve(t_cmd *cmd, char **split_line, char *command, int *status);
// static int close_reopen_heredoc(void);
// static int write_heredoc_lines(int fd, char *limit);



#endif
