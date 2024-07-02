# include "lib/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <linux/limits.h>
# include <readline/readline.h>

// size_t	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// int ft_pwd (void)
// {
// 	char cwd[PATH_MAX];

// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 	{
// 		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
// 		write(STDOUT_FILENO, "\n", 1);
// 		return (EXIT_SUCCESS);
// 	}
// 	else
// 		return(EXIT_FAILURE);
// }

int main(int ac, char **av, char **envp)

{

    int fd = open(av[1], O_TRUNC | O_CREAT | O_RDWR, 0644);

    if (fd != -1)
        printf("fd: %d\n", fd);
	else
        perror("open"); // print error message if open fails
    return (EXIT_SUCCESS);

}