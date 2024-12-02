/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:01:33 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/15 22:54:08 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ignore_sigpipe(void)
{
	signal(SIGPIPE, SIG_IGN);
}

void	sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_signals(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signal_handler(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(signum, &sa, NULL);
}
