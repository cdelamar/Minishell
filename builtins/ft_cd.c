#include "../includes/minishell.h"

int	ft_cd(char *path, t_cmd *cmd)
{
	    if (chdir(path) != 0)
    {
        ft_putstr_fd("cd: no such file or directory: ", 1);
        ft_putstr_fd(path, 1);
        ft_putstr_fd("\n", 1);
        return (1);
    }
    return (0);
}