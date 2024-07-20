/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:58:53 by laubry            #+#    #+#             */
/*   Updated: 2024/07/20 21:40:35 by lucasaubry       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	side_quote(t_token *token, int i)
{
	t_token	*head;

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
	else if (head->type == DOUBLE_QUOTE || head->type == SIMPLE_QUOTE)
		return (2);
	else
		return (1);
}

void	delet_space(t_token **token, int i)
{
	t_token	*head;
	t_token	*temp;

	head = *token;
	while (head != NULL && i -1 != 0)
	{
		i--;
		head = head->next;
	}
	if (head == NULL)
		return ;
	temp = head->next;
	head->next = head->next->next;
	printf("removing item from list: %p\n", temp);
	ft_lstdelone(temp, free);
}

void	delet_space_fonc(t_token *head)
{
	t_token	*temp;

	while (head != NULL && head->next != NULL)
	{
		if (head->next->type == SPACES)
		{
			temp = head->next;
			head->next = head->next->next;
			ft_lstdelone(temp, free);
		}
		else
			head = head->next;
	}
}

int	process_quotes(t_token **token, int *j, t_token *place)
{
	int	boul;
	int	info_boul;

	info_boul = 0;
	boul = side_quote(*token, *j -1);
	if (boul == 1 || boul == 2)
	{
		if (boul == 2)
			delet_quote_inword(token, place);
		before_node_cat(token, *j -1);
		(*j)--;
	}
	else
		info_boul = 1;
	boul = side_quote(*token, *j +1);
	if (boul == 1 || boul == 2)
	{
		if (boul == 2)
		{
			delet_quote_inword(token, place);
			before_node_cat(token, *j);
		}
		else
			after_node_cat(token, *j);
		(*j)--;
	}
	else
		info_boul += 1;
	return (info_boul);
}

void	delet_quote_inword(t_token **token, t_token *place)
{
    t_token *head;
    int     i;
    int     k;
    char    *new_content;

	i = 0;
	k = 0;
   head = *token;
	while (head->index != place->index)
		head = head->next;
	new_content = malloc(ft_strlen(head->content) + 1);
	while (head->content[i])
    {
        if (head->content[i] != '"' && head->content[i] != '\'')
        {
            new_content[k] = head->content[i];
            k++;
        }
        i++;
    }
    new_content[k] = '\0';
    free(head->content);
    head->content = new_content;
	head->type = WORD;
}


void	after_before_cat(t_token **token)
{
	t_token	*head;
	int		j;
	int		adjacant;

	adjacant = 0;
	j = 0;
	head = *token;
	while (head != NULL)
	{
		if (head->type == DOUBLE_QUOTE || head->type == SIMPLE_QUOTE)
		{
			adjacant = process_quotes(token, &j, head);
			if (adjacant == 2)
				delet_quote_inword(token, head);
			head = *token;
			j = 0;
		}
		j++;
		head = head->next;
	}
	head = *token;
	delet_space_fonc(head);
}
