#include "../includes/minishell.h"

int handle_redirections(char **args)
{
    int i;
    int fd;

    i = 0;
    while (args[i])
    {
        if (ft_strcmp(args[i], ">") == 0)
        {
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                printf ("ERROR (redirection.c line 16)\n");
                return (EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }
        else if (ft_strcmp(args[i], ">>") == 0)
        {
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                printf ("ERROR (redirection.c line 28)\n");
                return (EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }
        else if (ft_strcmp(args[i], "<") == 0)
        {
            fd = open(args[i + 1], O_RDONLY);
            if (fd < 0)
            {
                printf ("ERROR (redirection.c line 40)\n");
                return (EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
        }
        else if (ft_strcmp(args[i], "<<") == 0)
        {
            if (ft_heredoc(args[i + 1]) != 0)
            {
                printf ("ERROR (redirection.c line 48)\n");
                return (EXIT_FAILURE);
            }
            args[i] = NULL;
        }
        i++;
    }
    return (0);
}