/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:32:50 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/25 10:25:19 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void initialize_cmd(t_cmd *cmd, char *line)
{
    cmd->fd_in = 0; // Initialize the input for the first commad
    cmd->path_command = ft_split(line, '|'); // maybe the issue of '|' = ctrl + d.
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


int handle_exit_command(char *line)
{
    if (ft_strcmp(line, "exit") == 0)
        return EXIT_COMMAND;
    return 0;
}

int	execute(char *line, t_cmd *cmd)
{
	printf ("** execute **\n");
	if (ft_strcmp(line, "|") == 0)
	{
		printf("synthax error : expected arguments with '|'\n");
		return (0);
	}

	if (line[0] == '\0')
	{
		printf("free : nothing outputed (exec.c : line 43)\n");
		return (0);
	}

	if (handle_exit_command(line) == EXIT_COMMAND)
		return (EXIT_COMMAND);
	if (ft_strchr(line, '|'))
		return (pipe_execute(line, cmd));
	else if (ft_builtin(line, cmd) == EXIT_SUCCESS)
	{
		printf("builtins succeed (exec.c line 52)\n");
		return (EXIT_SUCCESS);
	}
	else if (ft_strcmp(line, "exit") == 0)
		return (EXIT_COMMAND);
	return (basic_execute(line, cmd));
}
