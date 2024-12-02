/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:42:34 by laubry            #+#    #+#             */
/*   Updated: 2024/11/22 15:41:46 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_fonc(t_cmd *cmd, char *line)
{
	if (line == NULL)
	{
		ft_freetab(cmd->env);
		free_cmd(cmd);
		exit(g_signal);
	}
}

void	put_in_cmd(t_cmd *cmd, t_token **token_list)
{
	cmd->tokens = copy_token_list(*token_list);
	cmd->final_tab = main_cat(token_list);
	cmd->final_line = tab_to_str(cmd->final_tab);
}

int	in_loop(t_token **token_list, t_cmd *cmd)
{
	char	*line;
	char	**split_line;

	line = readline("$ ");
	split_line = ft_split_boosted(line);
	exit_fonc(cmd, line);
	add_history(line);
	if (!verif_line(line, split_line))
		return (1);
	if (!verif_make_token(line, split_line, token_list))
		return (0);
	free(line);
	free(split_line);
	return (2);
}

int	handle_loop(t_cmd **cmd, t_token **token_list, char ***tab)
{
	int	i;

	malloc_structs(cmd);
	(*cmd)->heredoc_processed = FALSE;
	(*cmd)->env = *tab;
	i = in_loop(token_list, *cmd);
	if (i == 1)
		return (1);
	else if (i == 0)
		return (0);
	path_main(token_list, *tab);
	if (*token_list == NULL)
		return (1);
	put_in_cmd(*cmd, token_list);
	token_lstclear(token_list, free);
	return (2);
}

int	handle_arguments(int argc)
{
	if (argc > 1)
	{
		g_signal = 0;
		return (check_error(ERROR_ARGS));
	}
	return (0);
}
