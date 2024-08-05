/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:23:37 by cdelamar          #+#    #+#             */
/*   Updated: 2024/08/05 15:23:39 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*path_finder(t_cmd *cmd, char *path, int size)
{
	int	i;

	i = 0;
	while (cmd->env[i] != NULL)
	{
		if (ft_strncmp(cmd->env[i], path, size) == 0)
			return (cmd->env[i] + 5);
		i++;
	}
	return (NULL);
}

void	ft_path(t_cmd *cmd)
{
	// printf ("path.c (line 19)\n");
	cmd->path = path_finder(cmd, "PATH=", 5);
	if (cmd->path)
		cmd->path_split = ft_split(cmd->path, ':');

	/*if ((!cmd->path) || (!cmd->path_command))
		return (1);
	return (0);*/
}