/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:13:04 by laubry            #+#    #+#             */
/*   Updated: 2024/07/10 18:46:54 by laubry           ###   ########.fr       */
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

void	lexer(t_token *token, char **strs)
{
	int		i;
	t_token	*head;

	i = 0;
	head = token;
	while (token)
	{
		token->content = strs[i];
		if (quote_verif(strs[i], 1))
			token->type = DOUBLE_QUOTE;
		else if (quote_verif(strs[i], 2))
			token->type = SIMPLE_QUOTE;
		else
			token->type = assign_enum(token);
		token = token->next;
		i++;
	}
}
