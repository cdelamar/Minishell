/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:32:50 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/18 17:15:40 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO : remove 'exit' from basic execute and put it in the builtins handler


void initialize_cmd(t_cmd *cmd, char *line)
{
    cmd->fd_in = 0; // Initialize the input for the first command
    cmd->path_command = ft_split(line, '|'); // maybe the issue of '|' = ctrl + d
}

void handle_error(char *msg, t_cmd *cmd, int *fd)
{
    printf("ERROR (%s)\n", msg);
    close_fds(fd);
    if (cmd->path_command)
        ft_freetab(cmd->path_command);
    //return(EXIT_FAILURE);
	exit(EXIT_FAILURE);
}

int	execute(char *line, t_cmd *cmd)
{
	if (line[0] == '\0')
	{
		printf("free (exec.c : line 38)\n");
		return (0);
	}
	if (ft_strchr(line, '|'))
		return (pipe_execute(line, cmd));
	else if (ft_builtin(line, cmd) == EXIT_SUCCESS)
		return (0);
	return (basic_execute(line, cmd));
}

	// else if (le builtin marche pas) ->error_message
