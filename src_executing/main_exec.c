/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:06:47 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/23 00:07:18 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	synthax_manager(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
		i++;
	if (ft_strcmp(split_line[i - 1], "|") == 0 || split_line[0][0] == '|' )
	{
		printf("synthax error near \"|\"\n");
		return (true);
	}
	if (ft_strcmp(split_line[0], "<") == 0 || ft_strcmp(split_line[0], ">") == 0
		|| ft_strcmp(split_line[0], "<<") == 0
		|| ft_strcmp(split_line[0], ">>") == 0)
	{
		printf("redirections : syntax error\n");
		g_signal = 2;
		return (true);
	}
	return (false);
}

void	process_input(t_cmd *cmd, t_token **token_list)
{
	if (synthax_manager(cmd->final_tab))
		return ;
	execute(cmd, token_list);
}

char	**cpy_tab(char **dest, char **src)
{
	int	len;

	len = -1;
	while (src[++len])
		dest[len] = ft_strdup(src[len]);
	dest[len] = NULL;
	return (dest);
}
