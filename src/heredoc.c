/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:59:33 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/23 21:38:56 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO croire en ses reves

// comment ca marche
// un fichier temporaire > open et unlink
// basic command sur la redi

/*
int ft_heredoc(char *limit)
{
    char *line ;
    char *heredoc_content ;

    line = readline("heredoc>");

    size_t length = 0;
    size_t capacity = 1024; // on teste des trucs a l'arrache pour linstant on mettra au propre apres

    // utiliser strjoin
    heredoc_content = (char *)malloc(capacity);
    if (!heredoc_content)
    {
        perror("malloc");
        return -1;
    }

    signals(); // Ensure signals are set up

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            free(heredoc_content);
            printf("CTRL + D\n");
            return -1;
        }

        // Check for the limit
        if (strcmp(line, limit) == 0)
        {
            free(line);
            break;
        }

        // Ensure enough space in the buffer
        length += strlen(line) + 1;
        if (length >= capacity)
        {
            capacity *= 2;
            heredoc_content = (char *)realloc(heredoc_content, capacity);
            if (!heredoc_content)
            {
                perror("realloc");
                free(line);
                return -1;
            }
        }

        strcat(heredoc_content, line);
        strcat(heredoc_content, "\n");
        free(line);
    }

    printf("Heredoc content:\n%s", heredoc_content);
    free(heredoc_content);

    return 0;
}*/


int ft_heredoc(char *limit)
{
    char *line;
    char *heredoc_content;
    char *temp;

    heredoc_content = (char *)malloc(1);
    if (!heredoc_content)
    {
        perror("malloc");
        return -1;
    }
    heredoc_content[0] = '\0'; // Initialize as empty string

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            free(heredoc_content);
            printf("CTRL + D\n");
            return -1;
        }

        // Check for the limit
        if (strcmp(line, limit) == 0)
        {
            free(line);
            break;
        }

        // Join the line and a newline to the heredoc content
        temp = ft_strjoin(heredoc_content, line);
        free(heredoc_content);
        heredoc_content = ft_strjoin(temp, "\n");
        free(temp);

        if (!heredoc_content)
        {
            perror("malloc");
            free(line);
            return -1;
        }

        free(line);
    }

    printf("Heredoc content:\n%s", heredoc_content);
    free(heredoc_content);

    return 0;
}