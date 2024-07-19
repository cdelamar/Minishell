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

int ft_heredoc(char *limit)
{
    char    *line;
    int     fd;

    fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        printf("ERROR heredoc.c : line 13\n");
        return(EXIT_FAILURE);
    }

    while (1)
    {
        printf("heredoc> ");
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break;

        // Remove 'trailing' newline character
        line[ft_strcspn(line, "\n")] = 0;

        // Check if it's the delimiter
        if (ft_strcmp(line, limit) == 0)
        {
            free(line);
            break;
        }

        // Write to the file
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
        return(EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);

    unlink("/tmp/heredoc_tmp");

    return (EXIT_SUCCESS);
}


/*
int ft_heredoc(char *limit)
{
    char    *line;
    int     fd;

	line = NULL;
	fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
    {
        printf("ERROR heredoc.c : line 13\n");
        return(EXIT_FAILURE);
    }

    while (1)
    {
        printf("heredoc> ");
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break;

        // r0emove 'trailing' newline charac
        line[ft_strcspn(line, "\n")] = 0;

        // on regarde si c'est pas le delimiteur
        if (ft_strcmp(line, limit) == 0)
        {
            free(line);
            break;
        }

		// WORK IN PROGRESS, test pour eviter de planter en cas de mauvais commande
		if (write(fd, line, strlen(line)) == -1 || write(fd, "\n", 1) == -1)
        {
            printf("ERROR (heredoc.c line 37)\n");
            free(line);
            close(fd);
            return (EXIT_FAILURE);
        }

        // et la bam affichage
        //printf("%s\n", line);
        free(line);
    }

    close(fd);

    // la va falloir revoir le truc parce que ca pars dans tous les sens
    fd = open("/tmp/heredoc_tmp", O_RDONLY);
    if (fd < 0)
    {
        printf("ERROR heredoc.c : line 45\n");
        return(EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);

    // Optionnel ???
    unlink("/tmp/heredoc_tmp");

    return (EXIT_SUCCESS);
}*/