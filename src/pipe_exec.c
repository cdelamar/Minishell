
#include "../includes/minishell.h"


static void setup_child_pipes(t_cmd *cmd, int *fd, int i) {
    dup2(cmd->fd_in, 0); // Get input from the previous command
    if (cmd->path_command[i + 1]) {
        dup2(fd[1], 1); // Output to the next command
    }
    close_fds(fd);
    close(cmd->fd_in);
}

static int child_process(t_cmd *cmd, int *fd, int i) {
    setup_child_pipes(cmd, fd, i);
    if (basic_execute(cmd->path_command[i], cmd) == EXIT_FAILURE)
    {
        ft_freetab(cmd->path_command);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

static void parent_process(t_cmd *cmd, int *fd, int *i)
{
    int	status;

    waitpid(cmd->pid1, &status, 0);
    close(fd[1]);
    if (cmd->fd_in)
        close(cmd->fd_in);
    cmd->fd_in = fd[0]; // save input for nxt command
    (*i)++;				// dunno why it work but dayum (indexing incrmt)
}

static int create_and_fork(t_cmd *cmd, int *fd)
{
    if (pipe(fd) < 0)
        handle_error("exec.c line 49", cmd, fd);
    cmd->pid1 = fork();
    if (cmd->pid1 < 0)
        handle_error("exec.c line 57", cmd, fd);
    return cmd->pid1;
}

int pipe_execute(char *line, t_cmd *cmd)
{
    int i = 0;

    initialize_cmd(cmd, line);

    while (cmd->path_command[i])
	{
        if (create_and_fork(cmd, cmd->fd) == 0)
            child_process(cmd, cmd->fd, i);
    	else
            parent_process(cmd, cmd->fd, &i);
    }

    close(cmd->fd_in);
    if (cmd->path_command)
        ft_freetab(cmd->path_command);
    return (EXIT_SUCCESS);
}
