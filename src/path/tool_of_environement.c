/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_of_environement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:11:13 by laubry            #+#    #+#             */
/*   Updated: 2024/07/24 19:10:57 by laubry           ###   ########.fr       */
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
	return (-1);
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
	while (word[i] != '"')
		i++;
	word[i] = '\0';
	return (word);
}

void	is_dollar_interogation(t_token *token_list)
{
	int	i;

	i = 0;
	if (token_list->content[i +1] == '?')
	{
		token_list->content[i] = g_var;
		token_list->content[i +1] = '\0';
		token_list->type = GLOBAL;
	}
}

void	path_other(char **envp, t_token *token_list, int place_of_dollar)
{
	t_token	*head;
	int		prefix;

	head = token_list;
	while (head->index < place_of_dollar)
		head = head->next;
	prefix = skip_prefix(head->content);
	getenv_in_list(envp, token_list, head->content + prefix, place_of_dollar);
}

int	nbr_of_dollar(t_token *token_list, int place_of_dollar)
{
	int	i;
	int	dollar;
	t_token *head;

	i = 0;
	dollar = 0;
	head = token_list;
	while (head->index < place_of_dollar)
		head = head->next;
	while (head->content[i] != '\0')
	{
		if (head->content[i] == '$')
			dollar++;
		i++;
	}
	return (dollar);
}

int	which_node(int	j, t_token *token_list)
{
	t_token *head;

	head = token_list;
	while (head != NULL && j != 0)
	{
		j--;
		head = head->next;
	}
	if (head == NULL)
		return (-1);
	return (head->index);
}



