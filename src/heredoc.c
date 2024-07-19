/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:59:33 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/18 17:16:32 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO fix heredoc

static int write_heredoc_lines(int fd, char *limit)
{
    char *line;

    while (1)
    {
        printf("heredoc> ");
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break;

        line[ft_strcspn(line, "\n")] = 0; // Remove trailing newline char

        if (ft_strcmp(line, limit) == 0)
        {
            free(line);
            break;
        }
        if (write(fd, line, strlen(line)) == -1 || write(fd, "\n", 1) == -1)
        {
            printf("ERROR writing to heredoc file (line %d : heredoc.c)\n", __LINE__);
            free(line);
            return (EXIT_FAILURE);
        }
        free(line);
    }
    return (EXIT_SUCCESS);
}

static int close_reopen_heredoc()
{
    int fd = open("/tmp/heredoc_tmp", O_RDONLY);
    if (fd < 0)
    {
        printf("ERROR reopening heredoc file (line %d : heredoc.c)\n", __LINE__);
        return (EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (EXIT_SUCCESS);
}

int ft_heredoc(char *limit)
{
    int fd = open_heredoc_file();
    if (fd < 0)
        return (EXIT_FAILURE);

    if (write_heredoc_lines(fd, limit) != EXIT_SUCCESS)
    {
        close(fd);
        unlink("/tmp/heredoc_tmp");
        return (EXIT_FAILURE);
    }

    close(fd);

    if (close_reopen_heredoc() != EXIT_SUCCESS)
    {
        unlink("/tmp/heredoc_tmp");
        return (EXIT_FAILURE);
    }

    unlink("/tmp/heredoc_tmp");
    return (EXIT_SUCCESS);
}

/*
int ft_heredoc(char *limit)
{
    printf ("inside heredoc\n");
    char    *line;
    int     fd;

    line = NULL;
    fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        printf("ERROR heredoc.c : line 13\n");
        return (EXIT_FAILURE);
    }

    while (1)
    {
        printf("heredoc> ");
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break;

        line[ft_strcspn(line, "\n")] = 0;  // Remove trailing newline char

        if (ft_strcmp(line, limit) == 0)
        {
            free(line);
            break;
        }

        if (write(fd, line, strlen(line)) == -1 || write(fd, "\n", 1) == -1)
        {
            printf("ERROR (heredoc.c line 37)\n");
            free(line);
            close(fd);
            return (EXIT_FAILURE);
        }

        free(line);
    }

    close(fd);

    fd = open("/tmp/heredoc_tmp", O_RDONLY);
    if (fd < 0)
    {
        printf("ERROR heredoc.c : line 45\n");
        return (EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);

    unlink("/tmp/heredoc_tmp");

    return (EXIT_SUCCESS);
}*/