/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:01:29 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/25 10:28:17 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO : handle '< test.txt cat' (*)
// TODO : handle 'cat <test.txt'
// TODO : handle ctrl+c in heredocs

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
        printf("ERROR redirection.c (line %d)\n", __LINE__);
        return (EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    args[i] = NULL;
    return (EXIT_SUCCESS);
}

int ft_heredoc_redirect(char *delim)
{
    if (!delim)
        return EXIT_FAILURE;
    if (ft_heredoc(delim) != 0)
        return EXIT_FAILURE;
    // printf("Heredoc redirection handled successfully.\n");
    return EXIT_SUCCESS;
}

int handle_redirections(char **args, int status, t_cmd *cmd)
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
		else if (ft_strcmp(args[i], "<<") == 0 && status == HEREDOC_ON)
        {
            // Only process the heredoc if it hasn't been processed yet
            if (args[i + 1] == NULL)
            {
                printf("bash: syntax error near unexpected token `newline`\n");
                return -1;
            }
            if (ft_heredoc(args[i + 1]) < 0)
                return -1;

            cmd->fd_in = open("/tmp/heredoc_tmp", O_RDONLY);
            if (cmd->fd_in < 0)
            {
                perror("ERROR opening heredoc temp file");
                return -1;
            }

            dup2(cmd->fd_in, STDIN_FILENO);
            close(cmd->fd_in);
            // Remove the heredoc elements from args for further processing
            free(args[i]);
            free(args[i + 1]);
            while (args[i + 2])
            {
                args[i] = args[i + 2];
                i++;
            }
            args[i] = NULL;
            i = 0; // Reset to recheck for more redirections
        }
        else
            i++;
    }
    return (EXIT_SUCCESS);
}
