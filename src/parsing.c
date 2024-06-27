/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:13:04 by laubry            #+#    #+#             */
/*   Updated: 2024/06/25 14:57:44 by laubry           ###   ########.fr       */
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
void	lexer(t_token *token, char **strs)
{
	int	i;
	t_token *head;

	i = 0;
	head = token;
	while(token)
	{
		token->content = strs[i];
		token->type = assign_enum(token);
		token = token->next;
		i++;
	}	
}

int find_the_dollar(t_token *token)
{
    while (token)
    {
        if (ft_strchr2(token->content, '$') == 1)
            return (token->index);
        token = token->next;
    }
    return -1; // une erreur quoi
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
	while(*env != NULL)
	{
		if (ft_strncmp(*env, word, len) == 0 && (*env)[len] == '=')
		{
			start = *env + len +1;
			while (place_of_dollar != token_list->index)
				token_list = token_list->next;
			token_list->content = realloc(token_list->content, ft_strlen(start) + 1);
			token_list->type = VAR;// lui atribuer lenum VAR
			strcpy(token_list->content, start);
			break;
		}
		env++;
	}
}

void	path_main(t_token *token_list, char **envp)
{
	int	place_of_dollar;
	t_token	*head;

	place_of_dollar = find_the_dollar(token_list);
	if (place_of_dollar == -1)
		return ;
	head = token_list;
	while (head->index < place_of_dollar)
		head = head->next;
	getenv_in_list(envp, token_list, head->content +1);// le +1 cest pour skip le $
}

