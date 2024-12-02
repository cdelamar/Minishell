/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:27:58 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/22 18:28:00 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**allocate_command_args(char **final_tab, int i)
{
	int	num_args;

	num_args = count_args(final_tab, i);
	return (malloc((num_args + 1) * sizeof(char *)));
}

void	finalize_commands(char ***commands, int cmd_index, int arg_index)
{
	commands[cmd_index][arg_index] = NULL;
	commands[cmd_index + 1] = NULL;
}

int	populate_commands(char ***commands, char **final_tab)
{
	int	cmd_index;
	int	arg_index;
	int	i;

	cmd_index = 0;
	arg_index = 0;
	i = 0;
	while (final_tab[i])
	{
		if (ft_strcmp(final_tab[i], "|") == 0)
		{
			handle_pipe_separator(commands, &cmd_index, &arg_index);
			i++;
			continue ;
		}
		if (arg_index == 0)
			commands[cmd_index] = allocate_command_args(final_tab, i);
		if (!commands[cmd_index])
			return (EXIT_FAILURE);
		commands[cmd_index][arg_index] = ft_strdup(final_tab[i]);
		arg_index++;
		i++;
	}
	finalize_commands(commands, cmd_index, arg_index);
	return (EXIT_SUCCESS);
}

char	***split_commands(char **final_tab)
{
	int		num_commands;
	char	***commands;

	num_commands = count_commands(final_tab);
	commands = malloc((num_commands + 1) * sizeof(char **));
	if (!commands)
		return (NULL);
	if (populate_commands(commands, final_tab) == EXIT_FAILURE)
	{
		free_commands(commands);
		return (NULL);
	}
	return (commands);
}
