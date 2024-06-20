#include "../includes/minishell.h"

int ft_echo (char **split_line, t_cmd *cmd)
{
	int		i;
	bool	newline;

	i = 2;
	newline = true;
	if (ft_strncmp(split_line[1], "-n", 2) == 0)
	{
		while (split_line[1][i++])
		{
			if (split_line[1][i] != 'n')
			{
				newline = false;
				break;
			}
		}
	}

	while (split_line[i])
	{
		ft_putstr_fd(split_line[i], 1);
		i++;
		if (split_line[i])
			ft_putchar_fd(' ', 1);
	}
	if (newline == true)
			ft_putchar_fd('\n', 1);
	ft_freetab(split_line);
	return (EXIT_SUCCESS);
}
