#include "minishell.h"

char	**malloc_tab(t_token **token)
{
	int		len;
	t_token	*head;

	head = *token;
	len = 0;
	while (head != NULL)
	{
		if (head->type != SPACES)
			len++;
		head = head->next;
	}
	return (malloc(sizeof(char *) * len +1));
}

int	check_is_space_node(char **str, int i)
{
	int	j;

	j = 0;
	if (str[i] == NULL)
		return (0);
	while (str[i][j] && str[i])
	{
		if (str[i][j] != ' ' && str[i][j] != '\t')
			return (0);
		j++;
	}
	return (1);
}

char	**mouve_str(char **str, int i)
{
	int	j;

	j = i + 1;
	while(str[j])
	{
		str[i] = str[j];
		str[j] = NULL;
		i++;
		j++;
	}
	return (str);
}

int	lstnew_with_cat(char **str, int i)
{
	int		boul;
	char	*temp;
	int		modif;

	modif = 0;
	boul = 0;
	//le node i est pas un espace si cest pas un espace check les node a cotr et fusion
	if (i > 0)
	{
		if (!check_is_space_node(str, i -1) && !check_is_space_node(str, i)
				&& str[i -1] != NULL && str[i] != NULL)
		{
			if (str[i -1] == NULL)
				temp = str[i];
			else
			{
				temp = ft_strjoin(str[i -1], str[i]);
				boul = 1;
			}
			free(str[i]);
			str[i] = ft_strdup(temp);
			if (boul == 1)
			{
				free(str[i -1]);
				str[i -1] = NULL;
				str = mouve_str(str, i - 1);
			}
			//lstnew avec les deux chaine 
			modif = 1;
		}	
	}
	boul = 0;
	if (!check_is_space_node(str, i +1)
		&& !check_is_space_node(str, i) && str[i +1] != NULL)
	{	
		if (str[i +1] == NULL)
			temp = str[i];
		else
		{	
			temp = ft_strjoin(str[i], str[i +1]);
			boul = 1;
		}
		free(str[i]);
		str[i] = ft_strdup(temp);
		if (boul == 1)
		{
			free(str[i + 1]);
			str[i + 1] = NULL;	// free apres pour veski les doubles
			str = mouve_str(str, i + 1);
		}
		//lstnew avec les deux chaine
		modif = 1;
	}
	return (modif);
}

void	cat_quote(char **tab_token, t_token **token)
{
	int	i;
	int	j;
	int	modif;

	i = 0;
	j = 0;
	modif = 0;
	while (tab_token[i])
		i++;
	token_lstclear(token, free);
	while (j != i)
	{
		modif = lstnew_with_cat(tab_token, j);
		j++;
		if (modif > 0)
			j = 0;
	}
//if (head->type == caracter de cmmnde (| < ex..) ne pas le fusioner si il est ocller a une quote)
}
/////////////////////////////////////////////////////////////////////////
int	add_node_with_cat(t_token **token_list, char **str, int i)
{
	t_token	*new_node;

	new_node = token_lstnew(str[i]);
	if (new_node == NULL)
		return (check_error(ERROR_NODE));
	new_node->index = i;
	token_lstadd_back(token_list, new_node);
	return (1);
}

void	tab_in_list(t_token **token, char **tab_token)
{
	int	i;

	i = 0;
	while (tab_token[i])
	{
		add_node_with_cat(token, tab_token, i);
		i++;
	}
}

void	main_cat(t_token **token)
{
	char	**tab_token;
	char	c;
	int		i;
	int		have_quote;
	t_token	*head;

	head = *token;
	have_quote = 0;
	i = 0;
	tab_token = malloc_tab(token);
	while (head != NULL)
	{
		if (head->content[0] == '\'' || head->content[0] == '"')
		{
			c = head->content[0];
			head = head->next;
			while (head && head->content[0] != c)
			{
				tab_token[i] = ft_strdup_for_quote(head->content);
				head = head->next;
				i++;
			}
			if (head)
				head = head->next; // pour veski la deuxiemes quote
			have_quote = 1;
		}
		else
		{
			tab_token[i] = ft_strdup(head->content);
			head = head->next;
			i++;
		}
	}
	tab_token[i] = NULL;
	if (have_quote == 1)
		cat_quote(tab_token, token);
	tab_token = delet_space_to_tab(tab_token);
	//tab_in_list(token, tab_token);
	i = 0;
	while (tab_token[i])
	{
		printf("tab == %s\n", tab_token[i]);
	//	free(tab_token[i]); // a metre en bas
		i++;
	}
//	free(tab_token); // a metre en bas
}
