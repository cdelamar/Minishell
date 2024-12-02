/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:25:34 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/29 21:31:33 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execve_or_exit(char *full_path, t_cmd *cmd, char ***commands)
{
	if (execve(full_path, cmd->path_command, cmd->env) == -1)
	{
		free(full_path);
		exit_with_error(NULL, cmd, commands);
	}
	free(full_path);
}

void	exit_with_clean(t_cmd *cmd, char ***commands, int exit_code)
{
	if (cmd->path_split)
		ft_freetab(cmd->path_split);
	free_cmd_resources(cmd);
	free_commands(commands);
	exit(exit_code);
}

void	exit_with_error(char *message, t_cmd *cmd, char ***commands)
{
	if (message)
		fprintf(stderr, "%s\n", message);
	free_cmd_resources(cmd);
	free_commands(commands);
	exit(EXIT_FAILURE);
}

void	finalize_execution(t_cmd *cmd)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	while (waitpid(-1, NULL, 1) > 0)
		;
}

void	handle_parent(t_cmd *cmd, pid_t pid)
{
	close(cmd->fd[1]);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	cmd->fd_in = cmd->fd[0];
	waitpid(pid, &cmd->status, 0);
}
