/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:59:58 by cdelamar          #+#    #+#             */
/*   Updated: 2024/01/11 18:42:08 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cleanup(t_pipex *pipex)
{
	free_tab((void **)pipex->split_paths);
}

static void	close_fds(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->infile);
	close(pipex->outfile);
}

static int	wait_for_childs(t_pipex *pipex)
{
	int	status;

	waitpid(pipex->pid1, &status, 0);
	waitpid(pipex->pid2, &status, 0);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		status;

	ft_init(argc, argv, envp, &pipex);
	ft_path(envp, &pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
	{
		cleanup(&pipex);
		ft_perror(FORK_FAILURE);
	}
	if (pipex.pid1 == 0)
		ft_child(argv, &pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
	{
		cleanup(&pipex);
		ft_perror(FORK_FAILURE);
	}
	if (pipex.pid2 == 0)
		ft_parent(argv, &pipex);
	close_fds(&pipex);
	status = wait_for_childs(&pipex);
	cleanup(&pipex);
	return (status);
}
