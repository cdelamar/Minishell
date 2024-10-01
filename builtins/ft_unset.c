/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:18:01 by cdelamar          #+#    #+#             */
/*   Updated: 2024/10/01 19:30:19 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool valid_charact(char *str)
{
	// Add logic to validate the identifier; ensure it doesn't contain '=', '?', etc.
	if (!str || !ft_isalpha(str[0])) // Must start with a letter
		return 0;
	int i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_') // Can only contain alphanumeric or '_'
			return (false);
		i++;
	}
	return (true);
}


int ft_unset(char **split_line, t_cmd *cmd)
{
	int i;
	int len;

	if (!split_line[1] || valid_charact(split_line[1]) == false)
		return (EXIT_FAILURE);
	i = 0;
	len = ft_strlen(split_line[1]);
	while (cmd->env[i] && !(strncmp(cmd->env[i], split_line[1], len) == 0 && cmd->env[i][len] == '='))
		i++;
	if (!cmd->env[i])
		return (EXIT_FAILURE);
	free(cmd->env[i]);
	while (cmd->env[i + 1])
	{
		cmd->env[i] = cmd->env[i + 1];
		i++;
	}
	cmd->env[i] = NULL;
	return (EXIT_SUCCESS);
}


