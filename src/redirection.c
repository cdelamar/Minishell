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

// TODO : handle '< test.txt cat' (*)
// TODO : handle ctrl+c in heredocs
// TODO : handle why '|' == ctrl + D

int ft_output_redirect(char **args, int i, int append)
{
    int fd;

    // (*) i think this if statement isnt flexible enough to handle redirection in every different ways
    if (!args[i + 1])
    {
        printf("Syntax error: expected file after redirection\n");
        return (EXIT_FAILURE);
    }

    fd = open(args[i + 1], O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), 0644);
    if (fd < 0)
    {
        printf("ERROR opening file (line %d : redirection.c)\n", __LINE__);
        return (EXIT_FAILURE);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    args[i] = NULL;
    return (EXIT_SUCCESS);
}

int ft_input_redirect(char **args, int i)
{
    int fd;

    if (!args[i + 1])
    {
        printf("Syntax error: expected file after redirection\n");
        return (EXIT_FAILURE);
    }
    fd = open_file(args[i + 1], O_RDONLY, 0);
    if (fd < 0)
    {
        printf("ERROR file descriptor (line %d : redirection.c)\n", __LINE__);
        return (EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    args[i] = NULL;
    return (EXIT_SUCCESS);
}

int ft_heredoc_redirect(char **args, int i)
{
    if (!args[i + 1])
	{
        printf("Syntax error: expected delimiter after '<<'\n");
        return (EXIT_FAILURE);
    }
    if (ft_heredoc(args[i + 1]) != 0)
	{
        printf("ERROR (line %d : redirection.c)\n", __LINE__);
        return (EXIT_FAILURE);
    }
    args[i] = NULL;
    return (EXIT_SUCCESS);
}

int handle_redirections(char **args) {
    int i = 0;

    while (args[i]) {
        if (ft_strcmp(args[i], ">") == 0) {
            if (ft_output_redirect(args, i, 0) != EXIT_SUCCESS) return (EXIT_FAILURE);
        } else if (ft_strcmp(args[i], ">>") == 0) {
            if (ft_output_redirect(args, i, 1) != EXIT_SUCCESS) return (EXIT_FAILURE);
        } else if (ft_strcmp(args[i], "<") == 0) {
            if (ft_input_redirect(args, i) != EXIT_SUCCESS) return (EXIT_FAILURE);
        } else if (ft_strcmp(args[i], "<<") == 0) {
            if (ft_heredoc_redirect(args, i) != EXIT_SUCCESS) return (EXIT_FAILURE);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

/*int handle_redirections(char **args)
{
    int i;
    int fd;

    i = 0;
    while (args[i])
    {
        if (ft_strcmp(args[i], ">") == 0)
        {
            if (!args[i + 1])
            {
                printf("Syntax error: expected file after '>'\n");
                return (EXIT_FAILURE);
            }
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                printf("ERROR (redirection.c line 16)\n");
                return (EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
            i++;
        }
        else if (ft_strcmp(args[i], ">>") == 0)
        {
            if (!args[i + 1])
            {
                printf("Syntax error: expected file after '>>'\n");
                return (EXIT_FAILURE);
            }
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                printf("ERROR (redirection.c line 28)\n");
                return (EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
            i++;
        }
        else if (ft_strcmp(args[i], "<") == 0)
        {
            if (!args[i + 1])
            {
                printf("Syntax error: expected file after '<'\n");
                return (EXIT_FAILURE);
            }
            fd = open(args[i + 1], O_RDONLY);
            if (fd < 0)
            {
                printf("ERROR (redirection.c line 40)\n");
                return (EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
            i++;
        }
        else if (ft_strcmp(args[i], "<<") == 0)
        {
            if (!args[i + 1])
            {
                printf("Syntax error: expected delimiter after '<<'\n");
                return (EXIT_FAILURE);
            }
            if (ft_heredoc(args[i + 1]) != 0)
            {
                printf("ERROR (redirection.c line 48)\n");
                return (EXIT_FAILURE);
            }
            args[i] = NULL;
            i++;
        }
        else
        {
            i++;
        }
    }
    return (EXIT_SUCCESS);
}*/

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