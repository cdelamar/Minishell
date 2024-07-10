#include "../includes/minishell.h"

int ft_heredoc(char *limit)
{
    char *line = NULL;
    int fd;

    // heredoc temporaire : buffer
    fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        printf("Failed HEREDOC\n");
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

        // et la bam affichage
        printf("%s\n", line);
        free(line);
        //printf("ALORS COUOUC OUAAAIs\n");
    }

    close(fd);

    // la va falloir revoir le truc parce que ca pars dans tous les sens
    fd = open("/tmp/heredoc_tmp", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return(EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);

    // Optionnel ???
    unlink("/tmp/heredoc_tmp");

    return (EXIT_SUCCESS);
}