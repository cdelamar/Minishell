/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:59:20 by laubry            #+#    #+#             */
/*   Updated: 2024/07/10 09:35:50 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_the_dollar(t_token *token)
{
	while (token)
	{
		if (ft_strchr2(token->content, '$') == 1)
			return (token->index);
		token = token->next;
	}
	return (-1); // une erreur quoi
}

int	skip_prefix(char *word)
{
	int	i;

	i = 0;
	while (word[i] != '$')
		i++;
	return (i +1);
}

char	*skip_sufix(char *word)
{
	int	i;

	i = 1;
	while (word[i] != '"') // metre '"' a la place de R
		i++;
//	i++;
	word[i] = '\0';
	return (word);
}

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

void	getenv_in_list(char **envp, t_token *token_list, char *word)
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
			while (find_the_dollar(token_list) != token_list->index)
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
	t_token *head;
	char	*word_clean;
	int		prefix;
	int		i;

	i = 0;
	head = token_list;
	while (head->index < place_of_dollar)
		head = head->next;
	prefix = skip_prefix(head->content);
	word_clean = skip_sufix(head->content);
	getenv_in_list(envp, token_list, word_clean + prefix);
	while (head->content[i])
		i++;
	head->content[i] = '"';
}

void	path_other(char **envp, t_token *token_list, int place_of_dollar)
{
	t_token *head;
	int		prefix;
	int		i;

	i = 0;
	head = token_list;
	while (head->index < place_of_dollar)
	head = head->next;
	prefix = skip_prefix(head->content);
	getenv_in_list(envp, token_list, head->content + prefix);
}

void	path_main(t_token *token_list, char **envp)
{
	int		place_of_dollar;
	t_token	*head;

	place_of_dollar = find_the_dollar(token_list);
	if (place_of_dollar == -1)
		return ;
	head = token_list;
	while (head->index < place_of_dollar)
		head = head->next;
	if (head->type == DOUBLE_QUOTE)
		path_double_quote(envp, token_list, place_of_dollar);
	else if (head->type == SIMPLE_QUOTE)
		return ;
	else
		path_other(envp, token_list, place_of_dollar);
}
// gere le $? et faire en sorte que le $autre ne segfault pas
