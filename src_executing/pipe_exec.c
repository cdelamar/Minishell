/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:23:45 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/23 01:34:18 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_pipes(t_cmd *cmd, char ***commands, int i)
{
	if (cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (commands[i + 1] != NULL)
		dup2(cmd->fd[1], STDOUT_FILENO);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
}

void	handle_child(char ***commands, int i, t_cmd *cmd, t_token **token_list)
{
	char	*full_path;

	signal(SIGPIPE, SIG_DFL);
	setup_pipes(cmd, commands, i);
	cmd->path_command = commands[i];
	if (handle_redirections(cmd->path_command, 0, cmd) == EXIT_FAILURE)
		exit_with_error("Error handling redirections", cmd, commands);
	if (is_builtin(cmd->path_command[0]))
	{
		execute_builtin_child(cmd, commands, token_list);
		exit(EXIT_SUCCESS);
	}
	full_path = get_cmd_path(cmd->path_command[0], cmd->env);
	if (full_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", cmd->path_command[0]);
		exit_with_error(NULL, cmd, commands);
	}
	execve_or_exit(full_path, cmd, commands);
}

int	dot_checker(char ***commands, int i)
{
	if (strcmp(commands[i][0], ".") == 0 ||
		strcmp(commands[i][0], "..") == 0)
	{
		fprintf(stderr, "%s: file argument required\n", commands[i][0]);
		g_signal = 127;
		return (1);
	}
	return (0);
}

int	execute_commands(char ***commands, t_cmd *cmd, t_token **token_list)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (commands[i] != NULL)
	{
		if (dot_checker(commands, i) == 1)
		{
			i++;
			continue ;
		}
		if (pipe(cmd->fd) == -1)
			return (EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			return (EXIT_FAILURE);
		if (pid == 0)
			handle_child(commands, i, cmd, token_list);
		else
			handle_parent(cmd, pid);
		i++;
	}
	finalize_execution(cmd);
	return (EXIT_SUCCESS);
}

int	pipe_execute(t_cmd *cmd, t_token **token_list)
{
	char	***commands;

	cmd->fd_in = 0;
	commands = split_commands(cmd->final_tab);
	if (!commands)
		return (EXIT_FAILURE);
	if (!check_all_commands_executable(commands, cmd->env))
	{
		free_commands(commands);
		return (EXIT_FAILURE);
	}
	if (execute_commands(commands, cmd, token_list) == EXIT_FAILURE)
	{
		free_commands(commands);
		return (EXIT_FAILURE);
	}
	free_commands(commands);
	return (EXIT_SUCCESS);
}
