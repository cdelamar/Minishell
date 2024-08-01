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

// TODO heredoc doesnt find proper command handlement
// MINISHELL>cat << EOF
// ** heredoc redirect : status = 1 **
// heredoc> this is
// heredoc> a test
// heredoc> EOF
// Heredoc output:
// this is
// a test
// Heredoc redirection handled successfully.
// cat: '<<': Aucun fichier ou dossier de ce nom
// cat: EOF: Aucun fichier ou dossier de ce nom
// MINISHELL>

int ft_heredoc(char *limit)
{
    char *line;
    int heredoc_fd;

    // Open a temporary file to store heredoc content
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
