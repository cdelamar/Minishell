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
		printf("array NUMBER %d : %s\n\n",i , tab[i]);
		i++;
	}
	printf("END OF PRINT TAB\n");
}

bool freeable_tab (char **tab)
{
	size_t	i;

	i = 0;
	while(tab[i])
		i++;

	if (i <= 1)
		return (false);
	return(true);
}

void free_cmd(t_cmd *cmd)
{
	if (cmd->path_command)
	{
		// printf("\n\n\n\n ________________FREEING PATH_COMD\n");
		// print_tab(cmd->path_command);
		ft_freetab(cmd->path_command);
	}
	if (cmd->path_split)
	{
		// printf("\n\n\n\n ________________FREEING PATH_SPLIT\n");
		// print_tab(cmd->path_split);
		ft_freetab(cmd->path_split);
	}

	free(cmd);
	//cmd = NULL;
}