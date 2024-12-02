/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 23:46:53 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/16 01:25:56 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_commands(char **final_tab)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (final_tab[i])
	{
		if (ft_strcmp(final_tab[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

int	count_args(char **final_tab, int start)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (final_tab[i] && ft_strcmp(final_tab[i], "|") != 0)
	{
		count++;
		i++;
	}
	return (count);
}

int	is_executable(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR)
		return (1);
	return (0);
}

void	handle_pipe_separator(char ***commands, int *cmd_index, int *arg_index)
{
	commands[*cmd_index][*arg_index] = NULL;
	(*cmd_index)++;
	*arg_index = 0;
}
