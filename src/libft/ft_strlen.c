#include "minishell.h"

size_t ft_strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

int	ft_strlen2(char *word)
{
	int	i;

	i = 0;
	while(word[i])
		i++;
	return (i);
}

