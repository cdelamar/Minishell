/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:32:50 by cdelamar          #+#    #+#             */
/*   Updated: 2024/09/06 00:42:57 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void cleanup(char *line, t_cmd *cmd)
{
	if(cmd)
    	free_structs(cmd);
    if(line)
		free(line);
}

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

int	execute(char *line, t_cmd *cmd)
{
	if (ft_strcmp(line, "|") == 0)
	{
		printf("synthax error : expected arguments with '|'\n");
		return (0);
	}

	if (syntax_redirect(line) == false)
		return (0);

	if (line[0] == '\0')
		return (0);

	if (ft_strchr(line, '|'))
		return (pipe_execute(line, cmd));
	else if (ft_builtin(line, cmd) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (basic_execute(line, cmd));
}
