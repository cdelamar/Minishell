#include "../includes/minishell.h"

// check man fork
// when pid < 0				: error
// when pid == 0			: child process
// else pid == child's ID	: parent process

// TODO : refactoring a more readable 'cmd_cat'
int execute (char *line, t_cmd *cmd)
{
	// if simple_command
	return(basic_execute(line, cmd));
	// if '$'
	//return(path_execute(line, cmd));
}

int basic_execute (char *line, t_cmd *cmd)
{
	char	*command;
	char	**split_line;
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
		ft_freetab(split_line);
		return (1); // error
	}

	// parent fork
	else
		sleep(1);
	return (0);
}