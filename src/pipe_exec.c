
#include "../includes/minishell.h"

void	handle_pipe_error(t_cmd *cmd, int *fd)
{
    printf("ERROR (pipe_exec.c line 6)\n");
    if (fd)
	{
        close(fd[0]);
        close(fd[1]);
    }
    ft_freetab(cmd->path_command);
}

void	handle_fork_error(t_cmd *cmd, int *fd)
{
    printf("ERROR (pipe_exec.c line 17)\n");
    close(fd[0]);
    close(fd[1]);
    ft_freetab(cmd->path_command);
}

void execute_child_process(t_cmd *cmd, int *fd, int i)
{
    dup2(cmd->fd_in, 0); // Get input from the previous command
    if (cmd->path_command[i + 1])
        dup2(fd[1], 1); // Output to the next command
    close(fd[0]);
    close(fd[1]);
    close(cmd->fd_in);

    if (basic_execute(cmd->path_command[i], cmd) == EXIT_FAILURE)
	{
        ft_freetab(cmd->path_command);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

void parent_process(t_cmd *cmd, int *fd, int *i)
{
    int status;
    waitpid(-1, &status, 0);
    close(fd[1]);
    if (cmd->fd_in)
        close(cmd->fd_in);
    cmd->fd_in = fd[0]; // Save the input for the next command
    (*i)++;
}

void init_cmd(t_cmd *cmd, char *line)
{
    cmd->fd_in = 0; // Initialize the input for the first command
    cmd->path_command = ft_split(line, '|');
}

int pipe_execute(char *line, t_cmd *cmd)
{
    int i;

    init_cmd(cmd, line);
    i = 0;
    while (cmd->path_command[i])
	{
        if (pipe(cmd->fd) < 0)
		{
            handle_pipe_error(cmd, cmd->fd);
            return EXIT_FAILURE;
        }

        cmd->pid1 = fork();
        if (cmd->pid1 < 0)
		{
            handle_fork_error(cmd, cmd->fd);
            return EXIT_FAILURE;
        }
        else if (cmd->pid1 == 0)
            execute_child_process(cmd, cmd->fd, i);
        else
            parent_process(cmd, cmd->fd, &i);
    }
    close(cmd->fd_in);
    if (cmd->path_command)
        ft_freetab(cmd->path_command);
    return EXIT_SUCCESS;
}