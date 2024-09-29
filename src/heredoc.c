/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:59:33 by cdelamar          #+#    #+#             */
/*   Updated: 2024/09/05 18:11:05 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern sig_atomic_t g_signal;

int ft_heredoc(char *limit)
{
    char *line;
    int heredoc_fd;

    g_signal = 0;
    heredoc_signals();

    heredoc_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (heredoc_fd < 0)
    {
        reset_signals();
        return -1;
    }

    while (1)
    {
        if (g_signal == 1) // Check if SIGINT was triggered
        {
            close(heredoc_fd);
            unlink("/tmp/heredoc_tmp");
            reset_signals();
            return 130; // Exit code for interruption
        }

        line = readline("heredoc> ");
        // ctrl + c
        if (!line)
        {
            printf("ctrl + c\n");
            close(heredoc_fd);
            reset_signals();
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
    reset_signals();
    return 0;
}