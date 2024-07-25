/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:01:29 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/25 04:07:28 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO : handle '< test.txt cat' (*)
// TODO : handle 'cat <test.txt'
// TODO : handle ctrl+c in heredocs
// TODO : handle why '|' == ctrl + D

int ft_output_redirect(char **args, int i, int append)
{
    int fd;
	int flags;

    // (*) maybe need to merge with parsing for it
    if (!args[i + 1])
    {
        printf("Syntax error: expected file after redirection\n");
        return (EXIT_FAILURE);
    }

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;

	fd = open(args[i + 1], flags, 0644);
    if (fd < 0)
    {
        printf("ERROR opening file (line 40)\n");
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
        printf("ERROR redirection.c (line 61)\n");
        return (EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    args[i] = NULL;
    return (EXIT_SUCCESS);
}

/*int ft_heredoc_redirect(char **args, int i)
{
    if (!args[i + 1])
    {
        printf("Syntax error: expected delimiter after '<<'\n");
        return EXIT_FAILURE;
    }
    if (ft_heredoc(args[i + 1]) != 0)
    {
        printf("ERROR (line 79 : redirection.c)\n");
        return EXIT_FAILURE;
    }
    args[i] = NULL; // Indicate that this argument has been handled
    args[i + 1] = strdup(HEREDOC_TMP_FILE); // Replace the delimiter with the temp file path
    printf("Heredoc redirection handled successfully.\n");
    return EXIT_SUCCESS;
}*/

int ft_heredoc_redirect(char *delim)
{
    if (!delim)
    {
        // printf("Syntax error: expected delimiter after '<<'\n");
        return EXIT_FAILURE;
    }
    if (ft_heredoc(delim) != 0)
    {
        // printf("ERROR (line 79 : redirection.c)\n");
        return EXIT_FAILURE;
    }
    // args[i] = NULL; // Indicate that this argument has been handled
    // args[i + 1] = HEREDOC_TMP_FILE; // Replace the delimiter with the temp file path
    printf("Heredoc redirection handled successfully.\n");
    return EXIT_SUCCESS;
}

int handle_redirections(char **args, int status)
{
    int i = 0;

    while (args[i])
	{
        if (ft_strcmp(args[i], ">") == 0)
		{
            if (ft_output_redirect(args, i, 0) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
        }
		else if (ft_strcmp(args[i], ">>") == 0)
		{
            if (ft_output_redirect(args, i, 1) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
        }
		else if (ft_strcmp(args[i], "<") == 0)
		{
            if (ft_input_redirect(args, i) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
        }
		else if (ft_strcmp(args[i], "<<") == 0 && status == 1)
		{
            // printf("heredoc fait\n");
            if (ft_heredoc_redirect(args[i + 1]) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
            // printf ("cest un franc succes mon jeune amis\n");
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

/*
int handle_redirections(char **args)
{
    int i = 0;

    while (args[i])
	{
        if (ft_strcmp(args[i], ">") == 0)
		{
            if (ft_output_redirect(args, i, 0) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
        }
		else if (ft_strcmp(args[i], ">>") == 0)
		{
            if (ft_output_redirect(args, i, 1) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
        }
		else if (ft_strcmp(args[i], "<") == 0)
		{
            if (ft_input_redirect(args, i) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
        }
		else if (ft_strcmp(args[i], "<<") == 0)
		{
            printf("heredoc fait\n");
            if (ft_heredoc_redirect(args[i + 1]) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
            printf ("cest un franc succes mon jeune amis\n");
        }
        i++;
    }
    return (EXIT_SUCCESS);
}*/

