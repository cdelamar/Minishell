/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:32:50 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/18 17:15:40 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute(char *line, t_cmd *cmd)
{
	if (line[0] == '\0')
	{
		printf("free (exec.c : line 7)\n");
		return (0);
	}
	if (ft_strchr(line, '|'))
		return (pipe_execute(line, cmd));
	else if (ft_builtin(line, cmd) == EXIT_SUCCESS)
		return (0);
	return (basic_execute(line, cmd));
}

	// else if (le builtin marche pas) ->error_message

int pipe_execute(char *line, t_cmd *cmd)
{
	int i;
	int fd[2];
	int status;
	pid_t pid;

	i = 0;
	cmd->fd_in = 0; // Initialize the input for the first command

	cmd->path_command = ft_split(line, '|');

	while (cmd->path_command[i])
	{
		if (pipe(fd) < 0)
		{
			printf("ERROR (exec.c line 30)\n");
			ft_freetab(cmd->path_command);
			return (EXIT_FAILURE);
		}

		pid = fork();
		if (pid < 0)
		{
			printf("ERROR (exec.c line 37)\n");
			close(fd[0]);
			close(fd[1]);
			ft_freetab(cmd->path_command);
			return (EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			dup2(cmd->fd_in, 0); // Get input from the previous command
			if (cmd->path_command[i + 1])
				dup2(fd[1], 1); // Output to the next command

			close(fd[0]);
			close(fd[1]);
			close(cmd->fd_in);

			if (basic_execute(cmd->path_command[i], cmd) == EXIT_FAILURE)
			{
				ft_freetab(cmd->path_command);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, &status, 0);
			close(fd[1]);
			if (cmd->fd_in)
				close(cmd->fd_in);
			cmd->fd_in = fd[0]; // Save the input for the next command
			i++;
		}
	}

	close(cmd->fd_in);
	if (cmd->path_command)
		ft_freetab(cmd->path_command);
	return (EXIT_SUCCESS);
}

int basic_execute (char *line, t_cmd *cmd)
{
	char	*command;
	char	**split_line;
	int		status;
	int		i;

	i = 0;
	split_line = NULL;
	// exit_handler
	if (strcmp(line, "exit") == 0)
		return(EXIT_COMMAND);
	ft_path(cmd);
	if (!cmd->path)
	{
		printf("command not found\n");
		return (EXIT_SUCCESS);
	}
	cmd->pid1 = fork();

	//  error fork
	if (cmd->pid1 < 0)
		return (1);

	// child fork
	else if (cmd->pid1 == 0)
	{
		split_line = ft_split(line, ' ');

		if (handle_redirections(split_line) < 0)
		{
			printf("ERROR (exec.c line 117)\n");
			return (EXIT_FAILURE);
		}
		command = cmd_finder(split_line, cmd);
		if(command)
			execve(command, split_line, cmd->env);
		printf ("incorrect inputs : exec.c (line 123)\n");
		ft_freetab(split_line);
		//return (EXIT_FAILURE); // error

		if(waitpid(cmd->pid1, &status, 0) == -1)
		{
			printf("freetab (exec.c TEST line 129)\n");
			ft_freetab(split_line);
			return (EXIT_FAILURE);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		{
			printf("freetab (exec.c TEST line 135)\n");
			ft_freetab(split_line);
			return (EXIT_FAILURE);
		}
		printf("parent fork() (exec.c TEST line 139)\n");
	}

	else
	{
		if(waitpid(cmd->pid1, &status, 0) == -1)
		{
			printf("freetab (exec.c line 146)\n");
			ft_freetab(split_line);
			return (EXIT_FAILURE);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		{
			printf("freetab (exec.c line 152)\n");
			ft_freetab(split_line);
			return (EXIT_FAILURE);
		}
		//printf("parent fork() (exec.c line 156)\n");
		//ft_freetab(split_line);
	}
	return (EXIT_SUCCESS);
}
