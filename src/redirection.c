/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:01:29 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/18 13:49:17 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO : handle '< test.txt cat'
// TODO : handle ctrl+c in heredocs
// TODO : handle why '|' == ctrl + D

int backup_fd(int *saved_stdin, int *saved_stdout) {
    *saved_stdin = dup(STDIN);
    if (*saved_stdin < 0)
        return -1;
    *saved_stdout = dup(STDOUT);
    if (*saved_stdout < 0) {
        close(*saved_stdin);
        return -1;
    }
    return 0;
}

void restore_fd(int saved_stdin, int saved_stdout) {
    dup2(saved_stdin, STDIN);
    close(saved_stdin);
    dup2(saved_stdout, STDOUT);
    close(saved_stdout);
}

int handle_redirections(char **args)
{
    int i = 0;
    int fd;

    while (args[i])
    {
        if (args[i][0] == '>' || args[i][0] == '<')
        {
            if (args[i + 1] == NULL)
            {
                printf("Syntax error near unexpected token '%s'\n", args[i]);
                return (EXIT_FAILURE);
            }

            if (ft_strcmp(args[i], ">") == 0)
            {
                fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0)
                {
                    printf("ERROR (redirection.c line 16)\n");
                    return (EXIT_FAILURE);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            else if (ft_strcmp(args[i], ">>") == 0)
            {
                fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd < 0)
                {
                    printf("ERROR (redirection.c line 28)\n");
                    return (EXIT_FAILURE);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            else if (ft_strcmp(args[i], "<") == 0)
            {
                fd = open(args[i + 1], O_RDONLY);
                if (fd < 0)
                {
                    printf("ERROR (redirection.c line 40)\n");
                    return (EXIT_FAILURE);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
            }
            else if (ft_strcmp(args[i], "<<") == 0)
            {
                if (ft_heredoc(args[i + 1]) != 0)
                {
                    printf("ERROR (redirection.c line 48)\n");
                    return (EXIT_FAILURE);
                }
            }
            args[i] = NULL;
            args[i + 1] = NULL;
            i++;
        }
        i++;
    }
    return (EXIT_SUCCESS);
}


/*
int handle_redirections(char **args)
{
    int i;
    int fd;

    i = 0;
    while (args[i])
    {
        if (ft_strcmp(args[i], ">") == 0)
        {
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                printf ("ERROR (redirection.c line 16)\n");
                return (EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }
        else if (ft_strcmp(args[i], ">>") == 0)
        {
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                printf ("ERROR (redirection.c line 28)\n");
                return (EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }
        else if (ft_strcmp(args[i], "<") == 0)
        {
            fd = open(args[i + 1], O_RDONLY);
            if (fd < 0)
            {
                printf ("ERROR (redirection.c line 40)\n");
                return (EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
        }
        else if (ft_strcmp(args[i], "<<") == 0)
        {
            if (ft_heredoc(args[i + 1]) != 0)
            {
                printf ("ERROR (redirection.c line 48)\n");
                return (EXIT_FAILURE);
            }
            args[i] = NULL;
        }
        i++;
    }
    return (EXIT_SUCCESS);
}*/