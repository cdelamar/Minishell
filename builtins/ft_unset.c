#include "../includes/minishell.h"

int ft_unset (char **split_line, t_cmd *cmd)
{
	int	i;
	int	j;
	int len;

	i = 0;
	len = ft_strlen(split_line[1]);
	while(cmd->env[i])
	{
		if(strncmp(cmd->env[i], split_line[1], len) == 0 && cmd->env[i][len] == '=')
			break;
		i++;
	}

	if (!cmd->env[i])
	{
		printf("ECHEC\n\n");
		// ft_freetab(split_line);
        return (EXIT_FAILURE);
	}
	j = i;

	while(cmd->env[j])
	{
		cmd->env[j] = cmd->env[j + 1];
		j++;
	}
	printf ("unset succeed\n\n");
	// ft_freetab(split_line);
	return (EXIT_SUCCESS);
}
