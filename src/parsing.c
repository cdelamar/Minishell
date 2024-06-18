/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:13:04 by laubry            #+#    #+#             */
/*   Updated: 2024/06/18 12:03:04 by lucasaubry       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// atribu un enum au args
int	assign_enum(t_token *token)
{
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
		token->type = assign_enum(token);
		token = token->next;
	}	

}

int	find_the_dollar(t_token *token)
{
	t_token	*head;

	head = token;
	while (ft_strcmp(head->content, "$") != 0)
		head = head->next;
	return (head->index);
}



void	ft_path_finder(t_token *token_list, char **envp, char *word)
{
    int	i;
	int	j;
	int	len;
	int	len_after_equal;

    i = 0;
	j = 0;
	len = ft_strlen2(word);
    while (ft_strncmp(envp[i], &word, len) != 0)//danger la decu si ca marche pas cest possible cest le path finder modifer
		i++;
	if (envp[i] == "=") // ca jsp si cest bon a teste mais skip le egale il est moche
		i++;
	len_after_equal = (ft_strlen_after_equal(envp, i));
	len = find_the_dollar(token_list);
	while (token_list->index != len)
		token_list = token_list->next;	
	token_list->content = realloc(len_after_equal);
	len = 0;
	while(envp[i] != " ")
	{
		token_list->content[len] = envp[i];
		i++;
		len++;
	}
}

void	path_main(t_token *token_list, char **envp)
{
	int	place_of_dollar;
	t_token	*head;

	place_of_dollar = find_the_dollar(token);
	head = token_list;
	while (head->index != place_of_dollar)
		head = head->next;
	head = head->next;
	ft_path_finder(token_list, envp, head->content);
}

