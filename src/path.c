#include "../includes/minishell.h"

static char	*path_finder(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (ft_strncmp(cmd->env[i], "PATH=", 5) != 0)
		i++;
	return (cmd->env[i] + 5);
}

void	ft_path(t_cmd *cmd)
{
	cmd->path = path_finder(cmd);
	cmd->path_split = ft_split(cmd->path, ':');
}