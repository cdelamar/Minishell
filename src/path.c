#include "../includes/minishell.h"

char	*path_finder(t_cmd *cmd, char *path, int size)
{
	int	i;

	i = 0;
	while (ft_strncmp(cmd->env[i], path, size) != 0)
		i++;
	return (cmd->env[i] + 5);
}

void	ft_path(t_cmd *cmd)
{
	cmd->path = path_finder(cmd, "PATH=", 5);
	cmd->path_split = ft_split(cmd->path, ':');
}