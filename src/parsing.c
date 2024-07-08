/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:13:04 by laubry            #+#    #+#             */
/*   Updated: 2024/07/08 12:06:04 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// atribu un enum au args
int	assign_enum(t_token *token)
{
	if (ft_strcmp(token->content, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token->content, "<") == 0
		|| ft_strcmp(token->content, ">") == 0
		|| ft_strcmp(token->content, ">>") == 0
		|| ft_strcmp(token->content, "<<") == 0)
		return (REDIRECTION);
	else if (!*token->content) // si largument c un \0
		return (END);
	else
		return (WORD);
}

//lexer = metre tout dans une liste chainee et metre des enum sur les args
void	lexer(t_token *token, char **strs)
{
	int		i;
	t_token	*head;

	i = 0;
	head = token;
	while (token)
	{
		token->content = strs[i];
		token->type = assign_enum(token);
		token = token->next;
		i++;
	}
}
