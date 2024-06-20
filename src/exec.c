#include "../includes/minishell.h"

int execute (char *line, t_cmd *cmd)
{
	// if simple_command
	if (ft_builtin(line, cmd) == EXIT_SUCCESS)
		return(0);
	// else if (le builtin marche pas) ->error_message
	else
		return(basic_execute(line, cmd));;
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
		return (EXIT_FAILURE); // error
	}
	// parent fork
	else
		sleep(1);
	return (EXIT_SUCCESS);
}
