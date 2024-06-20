#include "../includes/minishell.h"

//char *getcwd(char *buf, size_t size);

int ft_pwd (void)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	else
		return(EXIT_FAILURE);
}