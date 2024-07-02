#include "minishell.h"

int	check_is_quote(int i, char *s, char **lst, int j)
{
	int	start;
	int	word_len;
	char	c;

	start = 0;
	word_len = 0;
	if (s[i] == '"')
		c = '"';
	else
		c = '\'';
	if (!is_char[s -1])
		start = i;	
	i++;
	while (s[i] && s[i] != c)
		i++;
	word_len = i - start;
	lst[j++] = ft_substr(start, 0, word_len);	
	return (i)
}


void	split_in_tab(char *s, char **lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		i = skip_space(s, i);
		start = i;
		if (s[i] == '"' || s[i] == '\'')
		{
			 i = check_is_quote(i, s, lst, j);
			 j++;
		}
		else if (
	}
	i++;
}

//si echo"oui" print echooui en faite les "" concataine meme deriere

char **ft_split_boosted(char *s)
{
	char	**lst = NULL;

	lst = (char **)malloc((count_word(s) +1) * sizeof(char *));
	if (!lst || !s)
	{
		free(lst);
		return (0); // erreur malloc ou chaine vide
	}
//	split_in_tab(s, lst);	
//	printf("%zu\n", count_word(s));
	return (lst);
}



