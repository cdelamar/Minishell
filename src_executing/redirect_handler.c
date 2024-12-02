/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:28:13 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/30 00:17:32 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_output_redirection(char **split_line, int i, int append)
{
	if (ft_output_redirect(split_line, i, append) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	free(split_line[i]);
	free(split_line[i + 1]);
	shift_left(split_line, i);
	return (EXIT_SUCCESS);
}

int	handle_input_redirection(char **split_line, int i)
{
	if (ft_input_redirect(split_line, i) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	free(split_line[i]);
	free(split_line[i + 1]);
	shift_left(split_line, i);
	return (EXIT_SUCCESS);
}

int	handle_heredoc_redirection(char **split_line, int i, t_cmd *cmd)
{
	if (split_line[i + 1] == NULL)
	{
		printf("bash: syntax error near unexpected token `newline`\n");
		return (-1);
	}
	if (ft_heredoc_redirect(split_line[i + 1]) < 0)
	{
		printf("ft_heredoc return -1\n");
		return (-1);
	}
	cmd->fd_in = open("/tmp/oui_tmp", O_RDONLY);
	if (cmd->fd_in < 0)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		perror("Error opening heredoc temp file");
		return (-1);
	}
	dup2(cmd->fd_in, STDIN_FILENO);
	close(cmd->fd_in);
	free(split_line[i]);
	free(split_line[i + 1]);
	shift_left(split_line, i);
	return (EXIT_SUCCESS);
}

int	process_redirection_token(char **split_line, int *i, int status, t_cmd *cmd)
{
	if (ft_strcmp(split_line[*i], ">") == 0)
		return (handle_output_redirection(split_line, *i, 0));
	else if (ft_strcmp(split_line[*i], ">>") == 0)
		return (handle_output_redirection(split_line, *i, 1));
	else if (ft_strcmp(split_line[*i], "<") == 0)
		return (handle_input_redirection(split_line, *i));
	else if (ft_strcmp(split_line[*i], "<<") == 0 && status == HEREDOC_ON)
		return (handle_heredoc_redirection(split_line, *i, cmd));
	else
		(*i)++;
	return (EXIT_SUCCESS);
}
