/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:00:07 by cdelamar          #+#    #+#             */
/*   Updated: 2024/01/11 18:50:51 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_cmd_finder(char **split_paths, char *cmd)
{
	char	*command;
	int		i;

	i = 0;
	while (split_paths[i])
	{
		command = ft_triple_strjoin(split_paths[i], "/", cmd);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	ft_child(char **argv, t_pipex *pipex)
{
	char	**split_cmd;
	char	*cmd;

	dup2(pipex->fd[1], STDOUT_FILENO);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	close(pipex->infile);
	split_cmd = ft_split(argv[2], ' ');
	cmd = ft_cmd_finder(pipex->split_paths, split_cmd[0]);
	if (cmd)
		execve(cmd, split_cmd, pipex->envp);
	free_tab((void **)pipex->split_paths);
	free_tab((void **)split_cmd);
	free(cmd);
	ft_perror(CHILD_FAILURE);
}

void	ft_parent(char **argv, t_pipex *pipex)
{
	char	**split_cmd;
	char	*cmd;
	int		i;

	i = 0;
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	close(pipex->outfile);
	split_cmd = ft_split(argv[3], ' ');
	while (pipex->split_paths[i])
	{
		cmd = ft_triple_strjoin(pipex->split_paths[i++], "/", split_cmd[0]);
		if (cmd)
			execve(cmd, split_cmd, pipex->envp);
		free(cmd);
	}
	free_tab((void **)pipex->split_paths);
	free_tab((void **)split_cmd);
	ft_perror(PARENT_FAILURE);
}
