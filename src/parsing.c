/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:13:04 by laubry            #+#    #+#             */
/*   Updated: 2024/07/16 20:30:41 by laubry           ###   ########.fr       */
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

int	is_spaces(t_token *head, int i)
{
	while (i != 0)
	{
		head = head->next;
		i--;
	}
	if (head->type != SPACES)
		return (i);
	else
		return (-1);
}

int	before_quote(t_token *token, int i)
{
	t_token *head;

	head = token;
	while (i != 0)
	{
		i--;
		if (head == NULL)
			return (-1);
		head = head->next;
	}
	if (head == NULL)
		return (-1);
	else if (head->type == SPACES)
		return (0);
	else
		return (1);
}

void	delet_space(t_token *token, int i)
{
	t_token *head;
	t_token *temp;

	head = token;
	while (head != NULL && i -1 != 0)
	{
		i--;
		head = head->next;
	}
	if (head == NULL)
		return ;
	temp = head->next;
	head->next = head->next->next;
	ft_lstdelone(temp, free);
}

void	cat_quote(t_token *token)
{
	t_token *head;
	int	i;
	int	j;
	int	boul;

	i = 0;
	j = 0;
	boul = 0;
	head = token;
	while (head != NULL)
	{
		if (head->type == DOUBLE_QUOTE || head->type == SIMPLE_QUOTE)
		{
			boul = before_quote(token, j -1);
			if (boul == 1)
				printf("BEFORE_FONC\n");
			else if (boul == 0)
			{
				delet_space(token, j -1);
				j--;
			}
			boul = before_quote(token, j +1);
			if (boul == 1)
				printf("AFTER_FONC\n");
			else if (boul == 0)
			{
				delet_space(token, j +1);
				j--;
			}
		}
		i++;
		j++;
		head = head->next;
	}
}

//ca marche saufe dans echi gg"" gg ""f ff ou ca met deux before_fonc
//parce ce que quand tu delet un espace ca delete le node et donc quand tu recalcul bah il en manque  
//echo gg"" il est au deuxieme a 1 avant
//echo ""gg pas de soucis
