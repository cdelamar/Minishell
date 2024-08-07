/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:59:33 by cdelamar          #+#    #+#             */
/*   Updated: 2024/08/07 20:31:35 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO : handle "sort << "" "
// handle empty delimiter

// TODO ; handle "exit [un argument]" return " too many arguments"

extern sig_atomic_t g_signal;

int ft_heredoc(char *limit)
{

    printf ("HEREDOC : \n");
    char *line;
    int heredoc_fd;

    g_signal = 0;
    heredoc_signals();

    heredoc_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (heredoc_fd < 0)
    {
        perror("ERROR opening heredoc file");
        reset_signals();
        return -1;
    }

    while (1)
    {
        if (g_signal == 1) // check ctrl + C
        {
            printf ("signal = 1\n");
            close(heredoc_fd);
            unlink("/tmp/heredoc_tmp");
            reset_signals();
            return (130);
            //exit (130); // Define SIGINT
        }

        line = readline("heredoc> ");
        if (!line)
        {
            free(line);
            close(heredoc_fd);
            printf("Warning: EOF received\n");
            reset_signals();
            return -1;
        }

        if (ft_strcmp(line, limit) == 0)
        {
            printf ("free line\n");
            free(line);
            break;
        }

        printf ("write heredoc\n");
        write(heredoc_fd, line, ft_strlen(line));
        write(heredoc_fd, "\n", 1);
        free(line);
    }
    close(heredoc_fd);
    reset_signals();
    return 0;
}
