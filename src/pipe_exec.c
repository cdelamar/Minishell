/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:23:45 by cdelamar          #+#    #+#             */
/*   Updated: 2024/08/08 13:31:31 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


// TODO : fix   MINISHELL>qwwqls | wc
//              1       4      27

static void setup_child_pipes(t_cmd *cmd, int *fd, int i)
{
    dup2(cmd->fd_in, 0); // Get input from the previous command
    if (cmd->path_command[i + 1])
        dup2(fd[1], 1); // Output to the next command
    close_fds(fd);
    close(cmd->fd_in);
}

static int child_process(t_cmd *cmd, int *fd, int i)
{
    setup_child_pipes(cmd, fd, i);
    
    char **split_line = ft_split(cmd->path_command[i], ' ');

    if (ft_strcmp(split_line[0], "exit") == 0)
    {
        int exit_code = ft_exit(split_line, cmd);
        ft_freetab(split_line);
        exit(exit_code);
    }

    // If not 'exit', execute normally
    if (basic_execute(cmd->path_command[i], cmd) == EXIT_FAILURE)
    {
        ft_freetab(split_line);
        exit(EXIT_FAILURE);
    }
    ft_freetab(split_line);
    exit(EXIT_SUCCESS);
}

/*
static int child_process(t_cmd *cmd, int *fd, int i)
{
    setup_child_pipes(cmd, fd, i);
    if (basic_execute(cmd->path_command[i], cmd) == EXIT_FAILURE)
    {
        ft_freetab(cmd->path_command);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}*/

static void parent_process(t_cmd *cmd, int *fd, int *i)
{
    int	status;

    waitpid(cmd->pid1, &status, 0);
    close(fd[1]);
    if (cmd->fd_in)
        close(cmd->fd_in);
    cmd->fd_in = fd[0]; // save input for nxt command
    (*i)++;				// (indexing increment)
}

static int create_and_fork(t_cmd *cmd, int *fd)
{
    if (pipe(fd) < 0)
        handle_error("exec.c line 49", cmd, fd);
    cmd->pid1 = fork();
    if (cmd->pid1 < 0)
        handle_error("exec.c line 57", cmd, fd);
    return cmd->pid1;
}

int pipe_execute(char *line, t_cmd *cmd)
{
    int i = 0;

    initialize_cmd(cmd, line);

    while (cmd->path_command[i])
	{
        if (create_and_fork(cmd, cmd->fd) == 0)
            child_process(cmd, cmd->fd, i);
    	else
            parent_process(cmd, cmd->fd, &i);
    }

    close(cmd->fd_in);
    if (cmd->path_command)
        ft_freetab(cmd->path_command);
    return (EXIT_SUCCESS);
}
