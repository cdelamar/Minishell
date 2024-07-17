/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:27:10 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/17 20:15:37 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO : FIX FT_EXPORT

int	ft_builtin(char *line, t_cmd *cmd)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (handle_redirections(split_line) == EXIT_FAILURE)
	{
		ft_freetab(split_line);
		return (EXIT_FAILURE);
	}
	if (ft_strcmp(split_line[0], "unset") == 0)
		return (ft_unset(split_line, cmd));
	else if (ft_strcmp(split_line[0], "echo") == 0)
		return (ft_echo(split_line));
	else if (ft_strcmp(split_line[0], "cd") == 0)
		return (ft_cd(split_line[1]));
	else if (ft_strcmp(split_line[0], "export") == 0)
		return (ft_export(split_line, cmd));
	else if (ft_strcmp(line, "env") == 0)
	{
		ft_freetab (split_line);
		return (ft_env(cmd));
	}
	else if (ft_strcmp(line, "pwd") == 0)
	{
		ft_freetab (split_line);
		return (ft_pwd());
	}
	ft_freetab (split_line);
	return (EXIT_FAILURE);
}
