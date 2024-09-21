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

int set_command_path(t_cmd *cmd)
{
    //printf ("cest set_command path qui cree path_split\n");
    ft_path(cmd);
    if (!cmd->path)
    {
        printf("SET COMMAND PATH command not found\n");
        // ft_freetab(cmd->path_split);  //LEAK
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int basic_child_process(char *line, t_cmd *cmd)
{
    char **split_line;
    char *command;

    split_line = ft_split(line, ' ');
    if (!split_line)
        return (EXIT_FAILURE);

    if (handle_redirections(split_line, HEREDOC_ON, cmd) != 0)
    {
        ft_freetab(split_line);
        ft_freetab(cmd->path_command);
        return (EXIT_FAILURE);
    }

    command = cmd_finder(split_line, cmd);
    if (command)
        execve(command, split_line, cmd->env);

    printf("command not found: %s\n", line);
    ft_freetab(split_line);
    ft_freetab(cmd->path_split); //LEAK INESPERE
    free(cmd);
    return (EXIT_FAILURE);
}

int basic_parent_process(pid_t pid, char **split_line, t_cmd *cmd) // TODO free cmd->path_split
{
    int status;

    if (waitpid(pid, &status, 0) == -1)
    {
        printf("waitpid -1\n");
        if (split_line)
            ft_freetab(split_line);
        if (cmd->path_split)
            ft_freetab(cmd->path_split);
        return EXIT_FAILURE;
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
    {
        if (cmd->path_split)
            ft_freetab(cmd->path_split);
        if (split_line)
          ft_freetab(split_line);
        free(cmd); //tentative le 22/09
        return EXIT_FAILURE;
    }
    ft_freetab(split_line);
    return EXIT_SUCCESS;
}

int basic_execute(char *line, t_cmd *cmd)
{
    int exit_code;
    char **split_line = NULL;

    split_line = ft_split(line, ' ');
    exit_code = set_command_path(cmd);
    if (exit_code != EXIT_SUCCESS)
    {
        ft_freetab(split_line);
		free_structs(cmd);
        return exit_code;
    }
    cmd->pid1 = fork();
    if (cmd->pid1 < 0)
    {
        printf("fork error\n");
        return EXIT_FAILURE; //Error forking
    }
    else if (cmd->pid1 == 0)
	{
        exit_code = basic_child_process(line, cmd);
        ft_freetab(split_line);
        exit(exit_code); // sans ca le code se dedouble en cas de fausse commande
    }
	else
        return basic_parent_process(cmd->pid1, split_line, cmd);
    ft_freetab(cmd->path_split);
    ft_freetab(split_line);
    return EXIT_SUCCESS;
}
