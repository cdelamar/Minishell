/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:18:01 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/16 17:25:36 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(char **split_line, t_cmd *cmd)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(split_line[1]);
	while (cmd->env[i])
	{
		if (strncmp(cmd->env[i], split_line[1], len) == 0
			&& cmd->env[i][len] == '=')
			break ;
		i++;
	}
	if (!cmd->env[i])
	{
		ft_freetab(split_line);
		return (EXIT_FAILURE);
	}
	j = i;
	while (cmd->env[j])
	{
		cmd->env[j] = cmd->env[j + 1];
		j++;
	}
	ft_freetab (split_line);
	return (EXIT_SUCCESS);
}
