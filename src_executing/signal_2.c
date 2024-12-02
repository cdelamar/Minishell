/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:53:57 by laubry            #+#    #+#             */
/*   Updated: 2024/11/15 23:44:22 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signals(void)
{
	setup_signal_handler(SIGINT, sigint_handler);
	setup_signal_handler(SIGQUIT, SIG_IGN);
	setup_signal_handler(SIGPIPE, SIG_IGN);
}

void	reset_signals(void)
{
	setup_signal_handler(SIGINT, SIG_DFL);
	setup_signal_handler(SIGQUIT, SIG_DFL);
}

void	print_token_list(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		printf("Index: %d\n", current->index);
		printf("Type: %s\n", get_token_type(current->type));
		printf("Content: %s\n", current->content);
		printf("\n");
		current = current->next;
	}
}

void	free_commands(char ***commands)
{
	int	i;
	int	j;

	i = 0;
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			free(commands[i][j]);
			j++;
		}
		free(commands[i]);
		i++;
	}
	free(commands);
}

void	free_cmd_resources(t_cmd *cmd)
{
	ft_freetab(cmd->final_tab);
	ft_freetab(cmd->env);
	free(cmd->final_line);
	token_lstclear(&cmd->tokens, free);
	free(cmd);
}
