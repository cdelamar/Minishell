/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:28:06 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/29 21:30:37 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_command_executable(char **command, char **env)
{
	char	*path;

	if (is_builtin(command[0]))
		return (1);
	path = get_cmd_path(command[0], env);
	if (path == NULL)
	{
		if (ft_strcmp(command[0], "<") == 0
			|| ft_strcmp(command[0], ">") == 0
			|| ft_strcmp(command[0], "<<") == 0
			|| ft_strcmp(command[0], ">>") == 0)
			printf("redirections : syntax error\n");
		else
			fprintf(stderr, "%s: command not found\n", command[0]);
		return (0);
	}
	free(path);
	return (1);
}

int	validate_commands(char ***commands, char **env)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
	{
		if (!is_command_executable(commands[i], env))
			return (0);
		i++;
	}
	return (1);
}

int	check_all_commands_executable(char ***commands, char **env)
{
	return (validate_commands(commands, env));
}

void	execute_builtin_child(t_cmd *cmd, char ***commands,
	t_token **token_list)
{
	if (pipe_builtin(cmd, cmd->path_command, token_list, commands)
		== EXIT_SUCCESS)
		exit_with_clean(cmd, commands, EXIT_SUCCESS);
	else
		exit_with_clean(cmd, commands, EXIT_FAILURE);
}
