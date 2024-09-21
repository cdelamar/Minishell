#include "../includes/minishell.h"

bool space_only (char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

void print_tab(char **tab)
{
	int i = 0;

	while(tab[i])
	{
		printf("array 1 : %s/n", tab[i]);
		i++;
	}
}