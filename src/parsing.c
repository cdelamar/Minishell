/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:13:04 by laubry            #+#    #+#             */
/*   Updated: 2024/06/23 21:26:31 by lucasaubry       ###   ########.fr       */
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

int find_the_dollar(t_token *token)
{
    while (token)
    {
		printf("token in while\n");
        if (ft_strchr2(token->content, '$') == 1)
		{
			printf("index :dddddddddddddddd %d\n", token->index);
            return (token->index);
		}
        token = token->next;
    }
    return -1; // une erreur quoi
}

void	put_word_in_token(char **envp, t_token *token_list, char *word)
{
	char		**env = envp;
	size_t		len;
	char		*start;
	char		*end;

	len = ft_strlen(word);
	while(*env != NULL)
	{
		if (ft_strncmp(*env, word, len) == 0)
		{
			start = *env + len;
			end = ft_strchr(start, ' ');
			if (end)
				len = end - start;
			else
				len = ft_strlen(start);
			token_list->content = realloc(token_list->content, len + 1);
			ft_strncpy(token_list->content, start, len);
			token_list->content[len] = '\0';
			break;
		}
		env++;
	}
}

void	path_main(t_token *token_list, char **envp)
{

	int	place_of_dollar = 10;
	t_token	*head;

	place_of_dollar = find_the_dollar(token_list);// segfault
	printf("place : %d\n", place_of_dollar);
	if (place_of_dollar == -1)
		return ;//erreur
	head = token_list;
	while (head->index != place_of_dollar)
		head = head->next;
	put_word_in_token(envp, token_list, head->content);
}

