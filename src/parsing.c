/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:13:04 by laubry            #+#    #+#             */
/*   Updated: 2024/07/30 10:37:06 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assign_enum(t_token *token)
{
	if (ft_strcmp(token->content, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token->content, "<") == 0
		|| ft_strcmp(token->content, ">") == 0
		|| ft_strcmp(token->content, ">>") == 0
		|| ft_strcmp(token->content, "<<") == 0)
		return (REDIRECTION);
	else if (ft_strcmp(token->content, " ") == 0)
		return (SPACES);
	else if (!*token->content)
		return (END);
	else
		return (WORD);
}

int	quote_verif(char *str, int j)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	if (j == 1)
		c = '"';
	else if (j == 2)
		c = '\'';
	if (str[i] == c)
		return (1);
	return (0);
}

int	quote_enum(t_token **token)
{
	char c;
	t_token	*head;

	head = *token;
	c = '\0';
	if (head->content[0] == '"')
	{
		head->type = DOUBLE_QUOTE;
		c = '"';
	}
	else if (head->content[0] == '\'')
	{
		head->type = SIMPLE_QUOTE;
		c = '\'';
	}
	else
		return (0);
	head = head->next;
	while (head->content[0] != c)
	{
		if (c == '"')
			head->type = DOUBLE_QUOTE;
		else
			head->type = SIMPLE_QUOTE;
		head = head->next;
	}
	if (c == '"')
		head->type = DOUBLE_QUOTE;
	else
		head->type = SIMPLE_QUOTE;
	*token = head;
	return (1);
}

void	lexer(t_token *token)
{
	t_token	*head;

	head = token;
	while (head)
	{
		if (!quote_enum(&head))
			head->type = assign_enum(head);
		head  = head->next;
	}
}
