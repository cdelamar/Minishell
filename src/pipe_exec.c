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
    dup2(cmd->fd_in, 0); // Get input from the previous command
    if (cmd->path_command[i + 1])
        dup2(fd[1], 1); // Output to the next command
    close_fds(fd);
    close(cmd->fd_in);
}

static int child_process(t_cmd *cmd, int *fd, int i)
{
    setup_child_pipes(cmd, fd, i);

    char **split_line;

    split_line = ft_split(cmd->path_command[i], ' ');
    // le split est pas bon :
    // en cas de commande erronee avec argument (ls | wc -dqwwqdqwd)
    // pas de leaks
    // en cas de commande erronee sans argument (ls | dqwwqdqwd)
    // ft_freetab libere pas correctement

    if (ft_strcmp(split_line[0], "exit") == 0)
    {
        int exit_code = ft_exit(split_line, cmd);
        ft_freetab(cmd->path_command); //LEAK
        ft_freetab(split_line);
        exit(exit_code);
    }


    // TODO FIX CE FOUTU INVALID READ QUAND ls | wc -dwqklwdqkqwd

    // If not 'exit', execute normally
    if (basic_execute(cmd->path_command[i], cmd) == EXIT_FAILURE)
    {
        //printf("EXECUTION FAILURE. ON FREE\n\n");
        //print_tab(split_line);
        if (cmd->path_split != NULL)
           ft_freetab(cmd->path_split); //LEAK BOSS*/
        if (cmd->path_command != NULL)
            ft_freetab(cmd->path_command); //LEAK
        free(cmd);
        //print_tab(split_line);
        ft_freetab(split_line);
        exit(EXIT_FAILURE);
    }
    if (cmd->path_split)
        ft_freetab(cmd->path_split); //LEAK BOSS
    ft_freetab(cmd->path_command); //LEAK
    ft_freetab(split_line);
    free(cmd);
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


int pipe_execute(char *line, t_cmd *cmd)
{
    int i = 0;
    pid_t last_pid = -1;

    initialize_cmd(cmd, line); //(cmd->path_command)

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
    printf("waitpid\n");
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
    //if (cmd->path_command)
    //    ft_freetab(cmd->path_command);
    //if(cmd->path_split)
    //    ft_freetab(cmd->path_split);
    //if (cmd)
    //    free(cmd); // POSSIBLE SUCCESS ??????
    printf("return success\n");
    return (EXIT_SUCCESS);
}

