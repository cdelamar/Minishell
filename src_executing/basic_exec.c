/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:24:07 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/30 02:26:29 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	syntax_redirect(char *line)
{
	int		i;
	char	**split_line;

	i = 0;
	split_line = ft_split(line, ' ');
	while (split_line[i] != NULL)
	{
		if ((strcmp(split_line[i], ">") == 0 && split_line[i + 1] != NULL
				&& strcmp(split_line[i + 1], ">") == 0)
			|| (strcmp(split_line[i], "<") == 0 && split_line[i + 1] != NULL
				&& strcmp(split_line[i + 1], "<") == 0))
		{
			printf("Error: consecutive redirections ('%s %s') not allowed.\n",
				split_line[i], split_line[i + 1]);
			ft_freetab(split_line);
			g_signal = 2;
			return (false);
		}
		i++;
	}
	ft_freetab(split_line);
	return (true);
}

int	ft_path_split(t_cmd *cmd)
{
	ft_path(cmd);
	if (!cmd->path)
	{
		printf("SET COMMAND PATH command not found\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	basic_parent_process(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		printf("waitpid -1\n");
		g_signal = 1;
		return (EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		g_signal = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal = 128 + WTERMSIG(status);
	return (EXIT_SUCCESS);
}
