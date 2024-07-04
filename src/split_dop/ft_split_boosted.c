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
//	if (!is_char(s[i -1]))
	start = i;	
	i++;
	while (s[i] && s[i] != c)
		i++;
	i++;
	word_len = i - start;
	lst[j++] = ft_substr(s + start, 0, word_len);	
	return (i);
}

int	check_is_compar(int i, char *s, char **lst, int j)
{
	char	c;
	int		word_len;
	int		start;

	start = i;
	word_len = 0;
	if (s[i] == '<')
		c = '<';
	else
		c = '>';
	if (s[i + 1] == c)
		i++;
	i++;
	word_len = i - start;
	lst[j] = ft_substr(s + start, 0, word_len);
	return (i);
}

int	check_is_pipe(int i, char *s, char **lst, int j)
{
	lst[j] = ft_substr(s + i, 0, 1);
	return (i + 1);
}
void	split_in_tab(char *s, char **lst)
{
	int	i;
	int	j;
	int	start;
	int	word_len;

	i = 0;
	j = 0;
	word_len = 0;
	start = 0;
	while (s[i])
	{
		i = skip_space(s, i);
		start = i;
		if (s[i] == '<' || s[i] == '>')
			i = check_is_compar(i, s, lst, j);
		else if (s[i] == '"' || s[i] == '\'')
			i = check_is_quote(i, s, lst, j);
		else if (s[i] == '|')
			i = check_is_pipe(i, s, lst, j);
		else
		{
			while (is_char(s[i]))
				i++;
			word_len = i - start;
			lst[j] = ft_substr(s + start, 0, word_len);
		}
		j++;
	}
	lst[j] = NULL;
}

//si echo"oui" print echooui en faite les "" concataine meme deriere

char **ft_split_boosted(char *s)
{
	char	**lst = NULL;
	int		word;

	word = count_word(s);
	if (word == 0)
		return (NULL);
	lst = (char **)malloc((word +1) * sizeof(char *));
	if (!lst)
		return (0); // erreur malloc
	split_in_tab(s, lst);	
//	printf("%zu\n", count_word(s));
	return (lst);
}



