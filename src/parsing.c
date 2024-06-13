/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:13:04 by laubry            #+#    #+#             */
/*   Updated: 2024/06/13 19:42:52 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// atribu un enum au args
int	assign_enum(t_token *token, int index)
{
	int	i;
	t_token *temp;

	i = 0;
	temp = token;
	printf("%d", index);
	while(i < index) // va jusqua la lindex pour lui atribuer un enum
	{
		temp = temp->next;
		i++;
	}
	if (ft_strcmp(token->content, "|") == 0)
	   return (PIPE);
	else if (ft_strcmp(token->content, "<") == 0 || ft_strcmp(token->content, ">") == 0 ||
		   	ft_strcmp(token->content, ">>") == 0 || ft_strcmp(token->content, "<<") == 0)
		return (REDIRECTION);
	else if (!*token->content) // si largument c un \0
		return (END);
	else
		return (WORD);

}

//lexer = metre tout dans une liste chainee et metre des enum sur les args
void	lexer(t_token *token, char **argv)
{
	int	i;
	t_token *head;

	i = 0;
	head = token;
	while(token)
	{
		token->content = argv[i];
		token = token->next;
		i++;
	}
	token = head;
	while(token)
	{
		token->type = assign_enum(token, token->index);
		token = token->next;
	}	

}
