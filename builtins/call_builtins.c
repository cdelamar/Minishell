/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:43:11 by laubry            #+#    #+#             */
/*   Updated: 2024/11/29 21:32:41 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_exit_cleanup(t_shell_context *ctx)
{
	if (ctx->to_free)
		free_commands(ctx->to_free);
	token_lstclear(&ctx->cmd->tokens, free);
	ft_freetab(ctx->cmd->env);
	if (ctx->cmd->path_split)
		ft_freetab(ctx->cmd->path_split);
	free(ctx->cmd->final_line);
	if (ctx->cmd->final_tab)
		ft_freetab(ctx->cmd->final_tab);
	free(ctx->cmd);
	restore_fd(ctx->saved[0], ctx->saved[1]);
	token_lstclear(ctx->token_list, free);
	exit(g_signal);
}

static int	handle_exit_builtin(t_shell_context *ctx)
{
	int	exit_code;

	exit_code = ft_exit(ctx->split_line, ctx->cmd);
	if (exit_code == -1)
		return (0);
	if (ctx->cmd->pid1 == 0)
		handle_exit_cleanup(ctx);
	return (exit_code);
}

static int	handle_builtins(char **split_line, t_cmd *cmd)
{
	if (ft_strcmp(split_line[0], "unset") == 0)
		return (ft_unset(split_line, cmd));
	else if (ft_strcmp(split_line[0], "echo") == 0)
		return (ft_echo(split_line));
	else if (ft_strcmp(split_line[0], "cd") == 0)
		return (ft_cd(split_line[1]));
	else if (ft_strcmp(split_line[0], "export") == 0)
		return (ft_export(split_line, cmd));
	else if (ft_strcmp(split_line[0], "env") == 0)
		return (ft_env(cmd));
	else if (ft_strcmp(split_line[0], "pwd") == 0)
		return (ft_pwd());
	return (EXIT_FAILURE);
}

int	builtin_commands(t_shell_context *ctx, int *saved)
{
	int	ret;

	ret = handle_builtins(ctx->split_line, ctx->cmd);
	if (ft_strcmp(ctx->split_line[0], "exit") == 0)
		ret = handle_exit_builtin(ctx);
	restore_fd(saved[0], saved[1]);
	return (ret);
}
