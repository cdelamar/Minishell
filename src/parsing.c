/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:13:04 by laubry            #+#    #+#             */
/*   Updated: 2024/08/21 14:58:49 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_quote(char *c, t_token *head)
{
	if (head->content[0] == '"')
	{
		head->type = DOUBLE_QUOTE;
		*c = '"';
		return (1);
	}
	else if (head->content[0] == '\'')
	{
		head->type = SIMPLE_QUOTE;
		*c = '\'';
		return (1);
	}
	else
		return (0);
}

int	quote_enum(t_token **token)
{
	char	c;
	t_token	*head;

	head = *token;
	c = '\0';
	if (!type_quote(&c, head))
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

void	lexer(t_token *token)
{
	t_token	*head;

	head = token;
	while (head)
	{
		if (!quote_enum(&head))
			head->type = assign_enum(head);
		head = head->next;
	}
}
