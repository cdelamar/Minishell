/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:59:33 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/30 02:00:32 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_heredoc(int *saved_stdin, int *heredoc_fd)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin < 0)
		return (-1);
	g_signal = 0;
	heredoc_signals();
	*heredoc_fd = open("/tmp/oui_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*heredoc_fd < 0)
	{
		reset_signals();
		dup2(*saved_stdin, STDIN_FILENO);
		close(*saved_stdin);
		return (-1);
	}
	return (0);
}

static int	handle_signal_interrupt(int heredoc_fd, int saved_stdin)
{
	if (g_signal == 1)
	{
		close(heredoc_fd);
		unlink("/tmp/oui_tmp");
		reset_signals();
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		return (130);
	}
	return (0);
}

static int	process_heredoc_line(char *line, char *limit, int heredoc_fd)
{
	if (!line)
	{
		close(heredoc_fd);
		reset_signals();
		return (0);
	}
	if (ft_strcmp(line, limit) == 0)
	{
		free(line);
		return (1);
	}
	write(heredoc_fd, line, ft_strlen(line));
	write(heredoc_fd, "\n", 1);
	free(line);
	return (0);
}

static int	handle_heredoc_loop(int heredoc_fd, int saved_stdin, char *limit)
{
	char	*line;
	int		res;

	while (1)
	{
		if (handle_signal_interrupt(heredoc_fd, saved_stdin) != 0)
			return (130);
		line = readline("heredoc> ");
		res = process_heredoc_line(line, limit, heredoc_fd);
		if (res == 1)
			break ;
		else if (res == 0 && !line)
		{
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			return (0);
		}
	}
	return (1);
}

int	ft_heredoc(char *limit)
{
	int		heredoc_fd;
	int		saved_stdin;
	int		res;

	if (init_heredoc(&saved_stdin, &heredoc_fd) < 0)
		return (-1);
	res = handle_heredoc_loop(heredoc_fd, saved_stdin, limit);
	if (res != 1)
		return (res);
	close(heredoc_fd);
	reset_signals();
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	return (0);
}
