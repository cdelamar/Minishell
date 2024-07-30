/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:59:20 by laubry            #+#    #+#             */
/*   Updated: 2024/07/28 02:21:03 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_in_tab(t_token *token_list, char *start)
{
	int		i;
	char	*s;
	char	*lst;

	i = 0;
	while (token_list->content[i] != '$')
		i++;
	s = malloc(sizeof(char) * i +1);
	i = 0;
	while (token_list->content[i] != '$')
	{
		s[i] = token_list->content[i];
		i++;
	}
	s[i] = '\0';
	free(token_list->content);
	lst = ft_strjoin(s, start);
	free(s);
	return (lst);
}

void	getenv_in_list(char **envp, t_token *token_list, char *word, int plc)
{
	char		**env;
	size_t		len;
	char		*start;

	env = envp;
	len = ft_strlen(word);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, word, len) == 0 && (*env)[len] == '=')
		{
			start = *env + len +1;
			while (plc != token_list->index)
				token_list = token_list->next;
			token_list->content = path_in_tab(token_list, start);
			if (token_list->type != DOUBLE_QUOTE)
				token_list->type = VAR;
			break ;
		}
		env++;
	}
}

void	path_double_quote(char **envp, t_token *token_list, int place_of_dollar)
{
	t_token	*head;
	char	*word_clean;
	//int		prefix;
	int		i;
	int		j;
	int		nbr_dollar;

	i = 0;
	j = 0;
	nbr_dollar = nbr_of_dollar(token_list, place_of_dollar);
	while (j != nbr_dollar)
	{
		place_of_dollar = which_node(j, token_list);
		if (place_of_dollar == -1)
			printf("caca");
		head = token_list;
		//prefix = skip_prefix(head->content);
		word_clean = skip_sufix(head->content) + skip_prefix(head->content);
		getenv_in_list(envp, token_list, word_clean, place_of_dollar);
		j++;
	}
	while (head->content[i])
		i++;
	head->content[i] = '"';
}

//char	*path_in_tab_quote(t_token *head, char *start, int *first_word)
//{
//	int		i;
//	char	*s;
//	char	*lst;
//
//	i = 0;
//	if (*first_word == 0)
//	{
//		*first_word = 1;
//		return (start);
//	}
//	printf("headddddd :%s\n", head->content);
//	while (head->content[i])
//		i++;
//	s = malloc(sizeof(char) * i +1);
//	i = 0;
//	while (head->content[i])
//	{
//		s[i] = head->content[i];
//		i++;
//	}
//	s[i] = '\0';
////	free(head->content);
//	lst = ft_strjoin(s, start);
//	free(s);
//	return (lst);
//}
//
//char	*no_path_in_tab(t_token *head, char *word)
//{
//	int		i;
//	char	*s;
//	char	*lst;
//
//	i = 0;
//	while (head->content[i])
//		i++;
//	s = malloc(sizeof(char) * i +1);
//	i = 0;
//	while (head->content[i])
//	{
//		s[i] = head->content[i];
//		i++;
//	}
//	s[i] = '\0';
////	free(head->content);
//	lst = ft_strjoin(s, word);
//	free(s);
//	return (lst);
//}
//
//void	getenv_in_list_quote(char **envp, t_token *head, char **tab_word, int plc)
//{
//	int		i;
//	int		first_word;
//	int		len;
//	char	**env;
//	char	*start;
//
//	i = 0;
//	first_word = 0;
//	env = envp;
//	while (tab_word[i])
//	{
//		len = ft_strlen(tab_word[i]);
//		start = NULL;
//		while (*env != NULL)
//		{
//			if (ft_strncmp(*env, tab_word[i], len) == 0 && (*env)[len] == '=')
//			{
//				start = *env + len +1;
//				while (plc != head->index)
//					head = head->next;
//				printf("startttt %s\n", start);
//				free(head->content);
//				head->content = path_in_tab_quote(head, start, &first_word);
//				break ;
//			}
//			env++;
//		}
//		if (start == NULL)
//		{
//		//	free(head->content);
//			head->content = no_path_in_tab(head, tab_word[i]);
//		}
//		env = envp;
//		i++;
//	}
//}
//
//void	path_double_quote(char **envp, t_token *token_list, int place_of_dollar)
//{
//	t_token *head;
//	char	**tab_word;
//	char	*word_clean;
//	int		prefix;
//	int		i;
//
//	i = 0;
//	head = token_list;
//	while (head->index < place_of_dollar)
//		head = head->next;
//	prefix = skip_prefix(head->content);
//	word_clean = skip_sufix(head->content);
//	tab_word = minisplit_dollar(word_clean + prefix);
//
//	getenv_in_list_quote(envp, head, tab_word, head->index);
//	
//	i = 0;
//	while (tab_word[i])
//	{
//		printf("tab_word :%s\n",tab_word[i]);
//		i++;
//	}	
//
//	(void)envp;
//	(void)place_of_dollar;
//}



void	path_main(t_token *token_list, char **envp)
{
	int		place_of_dollar;
	t_token	*head;

	head = token_list;
	while (head != NULL)
	{
		place_of_dollar = find_the_dollar(head);
		if (place_of_dollar == -1)
			return ;
		while (head->index < place_of_dollar)
			head = head->next;
		if (head->type == DOUBLE_QUOTE)
			path_double_quote(envp, token_list, place_of_dollar);
		else if (head->type == SIMPLE_QUOTE)
			return ;
		else
			path_other(envp, token_list, place_of_dollar);
		is_dollar_interogation(head);
		head = head->next;
	}
}// gere le $?






