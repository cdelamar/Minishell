#include "../includes/minishell.h"

// waitpid : les MACROS '<sys/wait.h>'

// WIFEXITED(status)
// retourne soit un non-zero(vrai) ou un zero(faux)
// vrai si le child s'est fini normalement

// WEXITSTATUS(status)
// #define WEXITSTATUS(status) (((status) & 0xff00) >> 8)
// is a macro that extracts the exit status of the child process
// (the value passed to exit or returned by main).
// nous nous intéressons aux bits de poids fort (bits 8 à 15) 
// car c'est là que le statut de sortie est stocké lorsque le processus se termine normalement. 
// WEXITSTATUS nous permet d'extraire ces bits pour obtenir le statut de sortie réel du processus enfant.

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
