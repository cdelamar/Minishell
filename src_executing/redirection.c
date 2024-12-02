/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:01:29 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/27 19:57:56 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_output_redirect(char **split_line, int i, int append)
{
	int	fd;
	int	flags;

	if (ft_strcmp(split_line[0], ">") == 0
		|| ft_strcmp(split_line[0], ">>") == 0)
		return (EXIT_FAILURE);
	if (!split_line[i + 1])
	{
		printf("Syntax error: expected file after redirection\n");
		g_signal = 2;
		return (EXIT_FAILURE);
	}
	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(split_line[i + 1], flags, 0644);
	if (fd < 0)
		return (EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(split_line[i]);
	split_line[i] = NULL;
	return (EXIT_SUCCESS);
}

void	shift_left(char **split_line, int start_index)
{
	int	i;

	i = start_index;
	while (split_line[i + 2])
	{
		split_line[i] = split_line[i + 2];
		i++;
	}
	split_line[i] = NULL;
	split_line[i + 1] = NULL;
}

int	ft_input_redirect(char **split_line, int i)
{
	int	fd;

	if (!split_line[i + 1])
	{
		printf("Syntax error: expected file after redirection\n");
		return (EXIT_FAILURE);
	}
	fd = open_file(split_line[i + 1], O_RDONLY, 0);
	if (fd < 0)
		return (EXIT_FAILURE);
	dup2(fd, STDIN_FILENO);
	close(fd);
	split_line[i] = NULL;
	return (EXIT_SUCCESS);
}

int	ft_heredoc_redirect(char *delim)
{
	if (!delim)
		return (EXIT_FAILURE);
	if (ft_heredoc(delim) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_redirections(char **split_line, int status, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (split_line[i])
	{
		if (process_redirection_token(split_line, &i, status, cmd)
			!= EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
