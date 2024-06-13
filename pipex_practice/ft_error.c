#include "pipex.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	error_message(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
}