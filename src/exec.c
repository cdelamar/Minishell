#include "../includes/minishell.h"

int execute (char *line, t_cmd *cmd)
{
	if (ft_strchr(line, '|'))
		return(pipe_execute(line, cmd));
	else if (ft_builtin(line, cmd) == EXIT_SUCCESS)
		return(0);
	// else if (le builtin marche pas) ->error_message
	else
		return(basic_execute(line, cmd));
}


int pipe_execute(char *line, t_cmd *cmd)
{
	int i;

	i = 0;
    cmd->path_command = ft_split(line, '|');
    while (cmd->path_command[i])
    {
        if (pipe(cmd->fd) < 0)
            return (EXIT_FAILURE);
        cmd->pid1 = fork();
        if (cmd->pid1 < 0)
            return (EXIT_FAILURE);
        else if (cmd->pid1 == 0)
        {
            dup2(cmd->fd_in, 0);
            if (cmd->path_command[i + 1])
                dup2(cmd->fd[1], 1);
            close(cmd->fd[0]);
            if (basic_execute(cmd->path_command[i], cmd) == EXIT_FAILURE)
                exit(EXIT_FAILURE);
            exit(EXIT_SUCCESS);
        }
        else
        {
            waitpid(cmd->pid1, &cmd->status, 0);
            close(cmd->fd[1]);
            cmd->fd_in = cmd->fd[0];
            i++;
        }
    }
    return (EXIT_SUCCESS);
}

int basic_execute (char *line, t_cmd *cmd)
{
	char	*command;
	char	**split_line;
	int		status; // work in progress
	int		i;

	i = 0;
	// exit_handler
	if (strcmp(line, "exit") == 0)
		return(EXIT_COMMAND);

	ft_path(cmd);
	cmd->pid1 = fork();
	//  error fork
	if (cmd->pid1 < 0)
		return (1);

	// child fork
	else if (cmd->pid1 == 0)
	{
		split_line = ft_split(line, ' ');
		command = cmd_finder(split_line, cmd);
		if(command)
			execve(command, split_line, cmd->env);
		printf ("incorrect inputs\n");
		ft_freetab(split_line);
		return (EXIT_FAILURE); // error
	}
	// parent fork
	else
	{
		if(waitpid(cmd->pid1, &status, 0) == -1)
			return (EXIT_FAILURE);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE) // TODO
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
