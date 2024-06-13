/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:00:18 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/13 13:10:38 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init(int argc, char **argv, char **envp, t_pipex *pipex)
{
	pipex->envp = envp;
	if (argc != 5)
		ft_perror(ARGC_FAILURE);
	pipex->infile = open(argv[1], O_RDONLY, 0644);
	if (pipex->infile == -1)
		ft_perror(IN_FAILURE);
	pipex->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->outfile == -1)
		ft_perror(OUT_FAILURE);
	if (pipe(pipex->fd) == -1)
		ft_perror(PIPE_FAILURE);
	pipex->cmd_nb = 0;
}

void	ft_perror(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	free_tab(void **tab)
{
	void	**_;

	_ = tab;
	while (*tab)
		free(*tab++);
	free(_);
}
