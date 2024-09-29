/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:23:45 by cdelamar          #+#    #+#             */
/*   Updated: 2024/09/04 22:46:23 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

static void setup_child_pipes(t_cmd *cmd, int *fd, int i)
{
    printf("\n\n dup2 \n\n");
    dup2(cmd->fd_in, 0); // Get input from the previous command
    if (cmd->path_command[i + 1])
        dup2(fd[1], 1); // Output to the next command
    close_fds(fd);
    close(cmd->fd_in);
}

static int child_process(t_cmd *cmd, int *fd, int i)
{
    setup_child_pipes(cmd, fd, i);

    if (basic_execute(cmd->path_command[i], cmd) == EXIT_FAILURE) // EXIT SUCCES OR EXIT FAILURE
    {
        free_cmd(cmd);
        printf("pipe child process : exit failure\n");
        exit(EXIT_FAILURE); // MAJOR success OR failure
    }
    printf("pipe_child\n");
    free_cmd(cmd);
    exit(EXIT_SUCCESS);
}

static void parent_process(t_cmd *cmd, int *fd, int *i)
{
    // Don't wait here; defer waiting to after the loop in pipe_execute
    close(fd[1]);
    if (cmd->fd_in)
        close(cmd->fd_in);
    cmd->fd_in = fd[0]; // save input for next command
    (*i)++;             // (indexing increment)
}

static int create_and_fork(t_cmd *cmd, int *fd)
{
    if (pipe(fd) < 0)
        handle_error("exec.c line 49", cmd, fd);
    //printf("-- ca fork dans le pipe --\n");
    cmd->pid1 = fork();
    if (cmd->pid1 < 0)
        handle_error("exec.c line 57", cmd, fd);
    return cmd->pid1;
}

/*
int pipe_execute(char *line, t_cmd *cmd)
{
    int i = 0;
    pid_t last_pid = -1;

    ft_path_command(cmd, line); //(cmd->path_command)

    while (cmd->path_command[i])
    {
        if (create_and_fork(cmd, cmd->fd) == 0)
            child_process(cmd, cmd->fd, i);
        else
        {
            last_pid = cmd->pid1; // Store the last child's PID
            parent_process(cmd, cmd->fd, &i);
        }
    }
    printf("((((((((((((((((((((((((((((((((waitpid\n");
    // Wait for the last command in the pipeline to finish
    int status;
    if (last_pid > 0)
    {
        printf ("lastpid = %d\n", last_pid);
        waitpid(last_pid, &status, 0);
    }
    // Reap any remaining child processes to avoid zombies
    while (waitpid(-1, NULL, WNOHANG) > 0); // ca va falloir le defendre
    close(cmd->fd_in);
    //free_cmd(cmd); // gaffe a ce que tu fais
    //eviter de free ici, vaut mieux le faire une fois return
    return (EXIT_SUCCESS);
}*/

int pipe_execute(char *line, t_cmd *cmd)
{
    int i = 0;
    pid_t last_pid = -1;

    ft_path_command(cmd, line); // Split command by pipe '|'

    while (cmd->path_command[i])
    {
        if (create_and_fork(cmd, cmd->fd) == 0)
        {
            // Child process
            child_process(cmd, cmd->fd, i);
        }
        else
        {
            // Parent process
            last_pid = cmd->pid1; // Store last child's PID
            parent_process(cmd, cmd->fd, &i);
        }
    }

    // Wait for the last command in the pipeline
    int status;
    if (last_pid > 0)
        waitpid(last_pid, &status, 0);

    // Wait for any remaining child processes
    while (waitpid(-1, NULL, WNOHANG) > 0);

    close(cmd->fd_in); // Close the last file descriptor

    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
        return (EXIT_SUCCESS);
    else
        return (EXIT_FAILURE);
}


