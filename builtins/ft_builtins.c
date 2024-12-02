/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:54:18 by laubry            #+#    #+#             */
/*   Updated: 2024/11/29 21:34:34 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_manager(char **split_line, int saved_stdin,
		int saved_stdout, t_cmd *cmd)
{
	if (handle_redirections(split_line, 0, cmd) == EXIT_FAILURE)
	{
		restore_fd(saved_stdin, saved_stdout);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	backup_manager(char **split_line, int *saved_stdin,
		int *saved_stdout, t_cmd *cmd)
{
	(void)split_line;
	if (backup_fd(saved_stdin, saved_stdout) < 0)
		return (EXIT_FAILURE);
	if (redirect_manager(split_line, *saved_stdin, *saved_stdout, cmd)
		== EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	is_builtin(char *command)
{
	if (!command)
		return (false);
	return (ft_strcmp(command, "unset") == 0
		|| ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "cd") == 0
		|| ft_strcmp(command, "export") == 0
		|| ft_strcmp(command, "env") == 0
		|| ft_strcmp(command, "pwd") == 0
		|| ft_strcmp(command, "exit") == 0);
}

int	pipe_builtin(t_cmd *cmd, char **command,
	t_token **token_list, char ***to_free)
{
	int				saved[2];
	int				ret;
	t_shell_context	ctx;

	ctx.split_line = command;
	ctx.cmd = cmd;
	ctx.saved = saved;
	ctx.token_list = token_list;
	ctx.to_free = to_free;
	if (backup_manager(command, saved, saved + 1, cmd) == EXIT_SUCCESS)
		ret = builtin_commands(&ctx, saved);
	else
		ret = EXIT_FAILURE;
	return (ret);
}

int	ft_builtin(t_cmd *cmd, t_token **token_list)
{
	char			**split_line;
	int				saved[2];
	int				ret;
	t_shell_context	ctx;

	split_line = cmd->final_tab;
	if (!split_line)
		return (EXIT_FAILURE);
	ctx.split_line = split_line;
	ctx.cmd = cmd;
	ctx.saved = saved;
	ctx.token_list = token_list;
	ctx.to_free = NULL;
	if (backup_manager(split_line, saved, saved + 1, cmd) == EXIT_SUCCESS)
		ret = builtin_commands(&ctx, saved);
	else
		ret = EXIT_FAILURE;
	return (ret);
}
