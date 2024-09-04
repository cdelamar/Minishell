/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:24:07 by cdelamar          #+#    #+#             */
/*   Updated: 2024/09/04 22:46:42 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO handle exit 0 | exit 1
// attention : tres chiant

#include "../includes/minishell.h"

bool syntax_redirect(char **split_line)
{
    int i = 0;

    while (split_line[i] != NULL)
    {
        if ((strcmp(split_line[i], ">") == 0 && split_line[i + 1] != NULL && strcmp(split_line[i + 1], ">") == 0) ||
            (strcmp(split_line[i], "<") == 0 && split_line[i + 1] != NULL && strcmp(split_line[i + 1], "<") == 0))
        {
            printf("Error: consecutive redirections ('%s %s') are not allowed.\n", split_line[i], split_line[i + 1]);
            return (true);
        }
        i++;
    }
    return false;
}

int set_command_path(t_cmd *cmd)
{
    ft_path(cmd);
    if (!cmd->path)
    {
        printf("command not found\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int basic_child_process(char *line, t_cmd *cmd)
{
    char **split_line;
    char *command;

    split_line = ft_split(line, ' ');

    if (syntax_redirect(split_line) == true)
    {
        printf ("je suis bien dans le true");
        ft_freetab(split_line);
        return(EXIT_FAILURE);
    }

    if (handle_redirections(split_line, HEREDOC_ON, cmd) != 0)
    {
        printf("ERROR (basic_exec.c line 25)\n");
        ft_freetab(split_line);
        return EXIT_FAILURE;
    }

    command = cmd_finder(split_line, cmd);
    if (command)
        execve(command, split_line, cmd->env);

    printf("command not found: %s\n", line);
    // free(cmd->env); //des projaires
    free_structs(cmd);
    ft_freetab(split_line);
    return EXIT_FAILURE;
}

int basic_parent_process(pid_t pid, char **split_line) // TODO free cmd->path_split
{
    int status;

    //printf("00 le waitpid du parent mais en basic 00\n");

    if (waitpid(pid, &status, 0) == -1)
    {
        printf("waitpid -1\n");
        if (split_line)
            ft_freetab(split_line);
        return EXIT_FAILURE;
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE) // cest la que ca peche ft_peche
    {
        printf("(line %d)\n", __LINE__);
        if (split_line)
          ft_freetab(split_line);
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
        printf("exit_code != EXIT_SUCCESS\n");
        ft_freetab(split_line);
		free_structs(cmd); // faut voir
        return exit_code;
    }
    //printf("00 ca fork dans le basic 00\n");
    cmd->pid1 = fork();
    if (cmd->pid1 < 0)
    {
        printf("ca fork pas chef\n");
        return EXIT_FAILURE; //Error forking
    }
    else if (cmd->pid1 == 0)
	{
        exit_code = basic_child_process(line, cmd);
        ft_freetab(split_line);
        exit(exit_code); // sans ca le code se dedouble en cas de fausse commande
    }
	else
        return basic_parent_process(cmd->pid1, split_line);
    ft_freetab(split_line);
    return EXIT_SUCCESS;
}
