/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:48:35 by laubry            #+#    #+#             */
/*   Updated: 2024/11/15 23:00:25 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	space_only(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("array %d : %s\n", i, tab[i]);
		i++;
	}
}

int	fork_error(t_cmd *cmd)
{
	printf("Fork error\n");
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	return (EXIT_FAILURE);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->path_command)
		ft_freetab(cmd->path_command);
	if (cmd->path_split)
		ft_freetab(cmd->path_split);
	if (cmd->final_tab)
		ft_freetab(cmd->final_tab);
	free(cmd);
}

char	*get_token_type(t_token_enum type)
{
	if (type == WORD)
		return ("WORD (Command)");
	else if (type == SPACES)
		return ("SPACES");
	else if (type == PIPE)
		return ("PIPE (|)");
	else if (type == REDIRECTION)
		return ("REDIRECTION");
	else if (type == VAR)
		return ("VAR ($)");
	else if (type == DOUBLE_QUOTE)
		return ("DOUBLE_QUOTE");
	else if (type == SIMPLE_QUOTE)
		return ("SIMPLE_QUOTE");
	else if (type == LAST_VERIF)
		return ("LAST_VERIF");
	else if (type == GLOBAL)
		return ("GLOBAL ($?)");
	else if (type == ERROR)
		return ("ERROR");
	else if (type == END)
		return ("END (\\0)");
	else
		return ("UNKNOWN");
}
