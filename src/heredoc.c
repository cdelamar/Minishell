/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:59:33 by cdelamar          #+#    #+#             */
/*   Updated: 2024/08/05 20:40:59 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO : handle "sort << "" "
// handle empty delimiter

int ft_heredoc(char *limit)
{
    char *line;
    int heredoc_fd;

    heredoc_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (heredoc_fd < 0)
    {
        perror("ERROR opening heredoc file");
        return -1;
    }

    while (1)
    {
        line = readline("heredoc> ");
        if (!line)
        {
            free(line);
            close(heredoc_fd);
            printf("Warning: EOF received\n");
            return -1;
        }

        if (ft_strcmp(line, limit) == 0)
        {
            free(line);
            break;
        }

        write(heredoc_fd, line, ft_strlen(line));
        write(heredoc_fd, "\n", 1);
        free(line);
    }
    close(heredoc_fd);
    return 0;
}
