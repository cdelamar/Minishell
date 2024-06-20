#include "../includes/minishell.h"

int ft_builtin(char *line, t_cmd *cmd)
{
	char **split_line;

	split_line = ft_split(line, ' ');
	if(ft_strncmp(split_line[0], "echo ", 5) == 0)
		return(ft_echo(split_line, cmd));
	if(ft_strcmp(line, "env ") == 0)
		return(ft_env(cmd));
}