/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:32:50 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/23 00:44:49 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_error(char *msg, t_cmd *cmd, int *fd)
{
	printf("ERROR (%s)\n", msg);
	close_fds(fd);
	if (cmd->path_command)
		ft_freetab(cmd->path_command);
	exit(EXIT_FAILURE);
}

bool	pipe_found(t_token *token_list)
{
	while (token_list != NULL)
	{
		if (token_list->type == PIPE)
			return (true);
		token_list = token_list->next;
	}
	return (false);
}

int	execute(t_cmd *cmd, t_token **token_list)
{
	if (ft_strcmp(cmd->final_line, "|") == 0)
	{
		printf("synthax error : expected arguments with '|'\n");
		return (0);
	}
	if (syntax_redirect(cmd->final_line) == false)
	{
		g_signal = 2;
		return (2);
	}
	if (cmd->final_line[0] == '\0')
		return (0);
	if (pipe_found(cmd->tokens) == true)
		return (pipe_execute(cmd, token_list));
	else
		return (basic_execute(cmd, token_list));
}
