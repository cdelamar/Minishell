#include "../includes/minishell.h"

int ft_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		ft_putstr_fd(cmd->env[i], 1);
		i++;
	}
	return (0);
}