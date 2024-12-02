/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:25:53 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/30 02:28:41 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_redirections_and_prepare(t_cmd *cmd, char **split_line)
{
	if (handle_redirections(split_line, HEREDOC_ON, cmd) != 0)
	{
		cmd->final_tab = NULL;
		ft_freetab(split_line);
		close(cmd->fd[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	execute_command_or_report_error(t_cmd *cmd, char *command,
				char **split_line)
{
	if (command)
	{
		close(cmd->fd[1]);
		execve(command, split_line, cmd->env);
	}
	else
	{
		printf("%s: command not found\n", split_line[0]);
		token_lstclear(&cmd->tokens, free);
		g_signal = 127;
	}
}

int	basic_child_process(t_cmd *cmd)
{
	char	**split_line;
	char	*command;

	split_line = cmd->final_tab;
	if (!split_line)
		return (EXIT_FAILURE);
	if (handle_redirections_and_prepare(cmd, split_line) != 0)
		return (EXIT_FAILURE);
	command = cmd_finder(split_line, cmd);
	execute_command_or_report_error(cmd, command, split_line);
	return (child_failure_signal(cmd, command, split_line));
}

int	basic_execute(t_cmd *cmd, t_token **token_list)
{
	int	exit_code;

	if (basic_setup(cmd) != EXIT_SUCCESS)
		return (g_signal);
	exit_code = ft_path_split(cmd);
	if (is_builtin(cmd->final_tab[0]) == true)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		return (ft_builtin(cmd, token_list));
	}
	if (exit_code != EXIT_SUCCESS)
		return (path_split_return(cmd));
	cmd->pid1 = fork();
	if (cmd->pid1 < 0)
		return (fork_error(cmd));
	else if (cmd->pid1 == 0)
		exit (ft_child(cmd, exit_code, token_list));
	else
		return (ft_parent(cmd, exit_code));
}
