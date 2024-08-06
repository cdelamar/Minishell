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

t_token	*lstnew_with_cat(char **str, int i)
{
	int	boul;
	char	*temp;
	boul = 0;
	//le node i est pas un espace si cest pas un espace check les node a cotr et fusion
	if (i > 0)
	{
		if (!check_is_space_node(str, i -1) && !check_is_space_node(str, i) && !str[i -1])
		{
			temp = ft_strjoin(str[i], str[i -1]);
			free(str[i]);
			str[i] = ft_strdup(temp);
			//lstnew avec les deux chaine 
	//		boul +=1;
		}	
	}
	if (!check_is_space_node(str, i +1) && !check_is_space_node(str, i) && str[i +1] != NULL)
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
		// a la place de free il faut que tu deplace tout dune case sur le free
		}
		//lstnew avec les deux chaine
	}
	return (token_lstnew(str[i]));
}

int	add_node_with_cat(t_token **token_list, char **str, int i)
{
	t_token	*new_node;

	new_node = lstnew_with_cat(str, i);
	if (new_node == NULL)
		return (check_error(ERROR_NODE));
	new_node->index = i;
	token_lstadd_back(token_list, new_node);
	return (1);
}

void	cat_quote(char **tab_token, t_token **token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab_token[i])
		i++;
	token_lstclear(token, free);
	while (j != i)
	{
		add_node_with_cat(token, tab_token, j);
		j++;
	}
//if (head->type == caracter de cmmnde (| < ex..) ne pas le fusioner si il est ocller a une quote)
}


void	main_cat(t_token **token)
{
	char	**tab_token;
	char	c;
	int		i;
	t_token	*head;

	head = *token;
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
				tab_token[i] = ft_strdup(head->content);
				head = head->next;
				i++;
			}
			if (head)
				head = head->next; // pour veski la deuxiemes quote
		}
		else
		{
			tab_token[i] = ft_strdup(head->content);
			head = head->next;
			i++;
		}
	}
	tab_token[i] = NULL;
	cat_quote(tab_token, token);
	i = 0;
	while (tab_token[i])
	{
		printf("tab == %s\n", tab_token[i]);
	//	free(tab_token[i]); // a metre en bas
		i++;
	}
//	free(tab_token); // a metre en bas
}
