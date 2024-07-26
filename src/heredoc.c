/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:59:33 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/25 10:25:05 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO croire en ses reves

// comment ca marche
// un fichier temporaire > open et unlink
// basic command sur la redi


int ft_heredoc(char *limit)
{
    char *line;
    char *heredoc_content;
    char *temp;

    heredoc_content = malloc(1);
    heredoc_content[0] = '\0';

    while (1)
    {
        line = readline("heredoc> ");
        if (!line)
        {
            free(heredoc_content);
            // printf("j'ai pas ctrl + D\n");
            return -1;
        }

        // Check for the limit
        if (ft_strcmp(line, limit) == 0)
        {
            free(line);
            break;
        }

        // Join the line and a newline to the heredoc content
        temp = ft_strjoin(heredoc_content, line);
        free(heredoc_content);
        heredoc_content = ft_strjoin(temp, "\n");
        free(temp);
        free(line);
    }

    printf("Heredoc output:\n%s", heredoc_content); // pas mal c'est francais
    free(heredoc_content);
    return 0;
}
