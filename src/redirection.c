#include "../includes/minishell.h"

int handle_redirections(char **args)
{
    int i = 0;
    int fd;

    while (args[i])
    {
        if (ft_strcmp(args[i], ">") == 0)
        {
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
                return (-1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }
        else if (ft_strcmp(args[i], ">>") == 0)
        {
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
                return (-1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }
        else if (ft_strcmp(args[i], "<") == 0)
        {
            fd = open(args[i + 1], O_RDONLY);
            if (fd < 0)
                return (-1);
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
        }
        else if (ft_strcmp(args[i], "<<") == 0)
        {
            if (ft_heredoc(args[i + 1]) != 0)
                return (-1);
            args[i] = NULL;
        }
        i++;
    }
    return (0);
}