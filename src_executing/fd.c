/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:23:59 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/29 23:56:30 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	open_file(char *filename, int flags, int mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	open_heredoc_file(void)
{
	int	fd;

	fd = open("/tmp/oui_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	backup_fd(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN);
	if (*saved_stdin < 0)
		return (-1);
	*saved_stdout = dup(STDOUT);
	if (*saved_stdout < 0)
	{
		close(*saved_stdin);
		return (-1);
	}
	return (0);
}

void	restore_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN);
	close(saved_stdin);
	dup2(saved_stdout, STDOUT);
	close(saved_stdout);
}
