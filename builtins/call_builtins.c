#include "../includes/minishell.h"

int ft_builtin(char *line, t_cmd *cmd)
{
	char **split_line;

	split_line = ft_split(line, ' ');

	if(ft_strncmp(split_line[0], "unset", 5) == 0)
		return (ft_unset(split_line, cmd));
	if(ft_strncmp(split_line[0], "echo", 4) == 0)
		return (ft_echo(split_line, cmd));
	if(ft_strcmp(line, "env") == 0)
		return (ft_env(cmd));
	if(ft_strcmp(line, "pwd") == 0)
		return (ft_pwd());
}