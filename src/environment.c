/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:59:20 by laubry            #+#    #+#             */
/*   Updated: 2024/07/09 18:17:48 by laubry           ###   ########.fr       */
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

	i = 0;
	while (word[i] != 'R')
		i++;
	i++;
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
	int			place_of_dollar;

	place_of_dollar = find_the_dollar(token_list);
	env = envp;
	len = ft_strlen(word);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, word, len) == 0 && (*env)[len] == '=')
		{
			start = *env + len +1;
			while (place_of_dollar != token_list->index)
				token_list = token_list->next;
			token_list->content = path_in_tab(token_list, start);
			token_list->type = VAR;
			break ;
		}
		env++;
	}
}

void	path_main(t_token *token_list, char **envp)
{
	int		place_of_dollar;
	t_token	*head;
	int		prefix;
	char	*word_clean;

	place_of_dollar = find_the_dollar(token_list);
	if (place_of_dollar == -1)
		return ;
	head = token_list;
	while (head->index < place_of_dollar)
		head = head->next;
	if (head->type != SIMPLE_QUOTE)
	{
		prefix = skip_prefix(head->content);
		word_clean = skip_sufix(head->content);
		getenv_in_list(envp, token_list, word_clean + prefix);
		prefix = 0;
		if (head->type == DOUBLE_QUOTE)
		{
			while (head->content[prefix])
				prefix++;
			head->content[prefix] = '"';
		}
	}
	return ;
}
