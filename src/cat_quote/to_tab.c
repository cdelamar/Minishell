#include "minishell.h"

char	**replace_x0_to_space(char **finish_tab)
{
	int	i;
	int	j;

	i = 0;
	while (finish_tab[i])
	{
		j = 0;
		while (finish_tab[i][j])
		{
			if (finish_tab[i][j] == '\x01')
				finish_tab[i][j] = ' ';
			else if (finish_tab[i][j] == '\x02')
				finish_tab[i][j] = '\t';
			j++;
		}
		i++;
	}
	return (finish_tab);
}

char	**delet_space_to_tab(char **tab_token)
{
	char	**finish_tab;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	while (tab_token[len])
		len++;
	finish_tab = malloc(sizeof(char *) * (len +1));
	while (i < len)
	{
		if (tab_token[i][0] != ' ' && tab_token[i][0] != '\t')
		{
			finish_tab[j] = malloc(sizeof(char *) * ft_strlen(tab_token[i]) + 1);
			ft_strcpy(finish_tab[j], tab_token[i]);
			j++;
		}
		i++;
	}
	finish_tab[i -1] = NULL;
	finish_tab = replace_x0_to_space(finish_tab);
	i = 0;
	return (finish_tab);
}
