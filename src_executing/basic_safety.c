/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_safety.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:25:17 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/23 00:08:39 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	basic_setup(t_cmd *cmd)
{
	if (ft_strcmp(cmd->final_tab[0], ".") == 0
		||ft_strcmp(cmd->final_tab[0], "..") == 0)
	{
		printf("minishell: %s: file argument required\n", cmd->final_tab[0]);
		g_signal = 127;
		return (g_signal);
	}
	if (ft_strcmp(cmd->final_tab[0], "$?") == 0)
	{
		printf("%d: command not found\n", g_signal);
		g_signal = 127;
		return (g_signal);
	}
	if (pipe(cmd->fd) == -1)
	{
		printf("pipe error\n");
		g_signal = 1;
		return (g_signal);
	}
	return (EXIT_SUCCESS);
}

int	path_split_return(t_cmd *cmd)
{
	printf("command not found: %s\n", cmd->final_line);
	g_signal = 127;
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	return (g_signal);
}

int	ft_child(t_cmd *cmd, int exit_code, t_token **token_list)
{
	close(cmd->fd[0]);
	exit_code = basic_child_process(cmd);
	free(cmd->final_line);
	if (cmd->final_tab)
		ft_freetab(cmd->final_tab);
	ft_freetab(cmd->env);
	ft_freetab(cmd->path_split);
	token_lstclear(&cmd->tokens, free);
	token_lstclear(token_list, free);
	free(cmd);
	exit (exit_code);
}

int	ft_parent(t_cmd *cmd, int exit_code)
{
	int	signal_value;

	close(cmd->fd[1]);
	exit_code = basic_parent_process(cmd->pid1);
	if (read(cmd->fd[0], &signal_value, sizeof(signal_value)) > 0)
		g_signal = signal_value;
	close(cmd->fd[0]);
	return (exit_code);
}

int	child_failure_signal(t_cmd *cmd, char *command, char **split_line)
{
	if (write(cmd->fd[1], (const void *)&g_signal, sizeof(g_signal)) == -1)
		printf("%s: command not found\n", split_line[0]);
	close(cmd->fd[1]);
	free(command);
	return (EXIT_FAILURE);
}
