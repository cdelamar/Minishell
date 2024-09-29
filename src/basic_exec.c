/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:24:07 by cdelamar          #+#    #+#             */
/*   Updated: 2024/09/06 00:44:21 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool syntax_redirect(char *line)
{
    int i = 0;
    char **split_line;

    split_line = ft_split(line, ' ');
    while (split_line[i] != NULL)
    {
        if ((strcmp(split_line[i], ">") == 0 && split_line[i + 1] != NULL && strcmp(split_line[i + 1], ">") == 0) ||
            (strcmp(split_line[i], "<") == 0 && split_line[i + 1] != NULL && strcmp(split_line[i + 1], "<") == 0))
        {
            printf("Error: consecutive redirections ('%s %s') are not allowed.\n", split_line[i], split_line[i + 1]);
            ft_freetab(split_line); //LEAK
            return (false);
        }
        i++;
    }
    ft_freetab(split_line); //LEAK
    return (true);
}

int ft_path_split(t_cmd *cmd)
{
    ft_path(cmd);
    if (!cmd->path)
    {
        printf("SET COMMAND PATH command not found\n");
        return (EXIT_FAILURE);
        //EXIT SUCCESS
    }
    return (EXIT_SUCCESS);
}

int basic_child_process(char **free_line, char *line, t_cmd *cmd)
{
    char **split_line;
    char *command;

    // printf("basic child\n\n");

    split_line = ft_split(line, ' ');
    if (!split_line)
        return (EXIT_FAILURE);

    if (handle_redirections(split_line, HEREDOC_ON, cmd) != 0)
    {
        ft_freetab(split_line);
        return (EXIT_FAILURE);
    }

    command = cmd_finder(split_line, cmd);
    if (command)
        execve(command, split_line, cmd->env);

    printf ("\n\n\n\n missing the execve command seems to occurs memory issues, but why\n\n\n\n");

    printf("%s : command not found\n", line);
    ft_freetab(split_line);
    ft_freetab(free_line);
    if (cmd->path_split)
        ft_freetab(cmd->path_split);
    if (cmd->path_command)
        ft_freetab(cmd->path_command);
    free(cmd);
    //free(line);
    //return (EXIT_FAILURE);
    //exit ?
    exit (EXIT_FAILURE);
}

int basic_parent_process(pid_t pid, char **split_line, t_cmd *cmd) // TODO free cmd->path_split
{
    int status;

    if (waitpid(pid, &status, 0) == -1)
    {
        printf("waitpid -1\n");
        //if (split_line)
        //    ft_freetab(split_line);
        return EXIT_FAILURE;
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
    {
        printf("WIFEXITED STATUS\n");
        //if (split_line)
        //  ft_freetab(split_line);
        //ft_freetab(cmd->path_split);
        return EXIT_FAILURE;
    }
    // printf("je suis le succes\n");
    //ft_freetab(split_line);
    return EXIT_SUCCESS;
}

// quel con, basic_execute est utilisee par pipe_exec si ya un pipe
// du coup, je libere pas squi ya dans pipe
/*
int basic_execute(char *line, t_cmd *cmd)
{
    int exit_code;
    char **split_line = NULL;

    split_line = ft_split(line, ' ');
    exit_code = ft_path_split(cmd); // path_split via ft_path
    if (exit_code != EXIT_SUCCESS)
    {
        printf("\n\n\nje suis peut etre la\n");
        ft_freetab(split_line);
		//free_structs(cmd);
        return exit_code;
    }
    cmd->pid1 = fork();
    printf("je suis peut etre ici la vu que je fork\n");

    if (cmd->pid1 < 0)
    {
        printf("fork error\n");
        ft_freetab(split_line);
        return EXIT_FAILURE; //Error forking
    }
    else if (cmd->pid1 == 0)
	{
        exit_code = basic_child_process(split_line, line, cmd);
        printf("exit code = %d\n", exit_code);
        ft_freetab(split_line);
        //ft_freetab(cmd->path_split);
        // MAJOR PROBLEM : FIX path_command free
        //ft_freetab(cmd->path_command);
        //free(cmd);
        exit(exit_code); // sans ca le code se dedouble en cas de fausse commande
    }
	else
    {
        printf("je suis peut etre la alors nan\n");
        //ft_freetab(split_line);
        //ft_freetab(cmd->path_split);
        //ft_freetab(cmd->path_command);
        //free(cmd);
        ft_freetab(split_line);
        return basic_parent_process(cmd->pid1, split_line, cmd); // EXIT_SUCCESS OR EXIT_FAILURE
    }
    printf("ca libere OKLM dans basic_exec\n");

    if (freeable_tab(split_line) == true)
        ft_freetab(split_line);
    else
        free(split_line);
    return EXIT_SUCCESS;
}*/


int basic_execute(char *line, t_cmd *cmd)
{
    int exit_code;
    char **split_line = NULL;

    split_line = ft_split(line, ' ');
    exit_code = ft_path_split(cmd); // Find command path

    if (exit_code != EXIT_SUCCESS)
    {
        printf("Command not found: %s\n", line);
        ft_freetab(split_line); // Free command split
        return exit_code;
    }

    cmd->pid1 = fork();
    if (cmd->pid1 < 0)
    {
        printf("Fork error\n");
        ft_freetab(split_line);
        return EXIT_FAILURE;
    }
    else if (cmd->pid1 == 0)
    {
        // Child process
        exit_code = basic_child_process(split_line, line, cmd);
        ft_freetab(split_line); // Free split in child process
        exit(exit_code);        // Avoid duplicate execution
    }
    else
    {
        // Parent process
        exit_code = basic_parent_process(cmd->pid1, split_line, cmd);
        ft_freetab(split_line); // Free split in parent process
        return exit_code;       // Return success or failure
    }
}
