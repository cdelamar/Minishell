/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:58:53 by laubry            #+#    #+#             */
/*   Updated: 2024/07/18 17:32:56 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	before_quote(t_token *token, int i)
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

void	process_quotes(t_token **token, int *j)
{
	int	boul;

	boul = before_quote(*token, *j -1);
	if (boul == 1)
	{
		before_node_cat(token, *j -1);
		(*j)--;
	}
	else if (boul == 0)
	{
		delet_space(token, *j -1);
		(*j)--;
	}
	boul = before_quote(*token, *j +1);
	if (boul == 1)
	{
		after_node_cat(token, *j);
		(*j)--;
	}
	else if (boul == 0)
	{
		delet_space(token, *j +1);
		(*j)--;
	}
	// printf ici des node 	
}

void	after_before_cat(t_token **token)
{
	t_token	*head;
	int		i;
	int		j;

	i = 0;
	j = 0;
	head = *token;
	while (head != NULL)
	{
		if (head->type == DOUBLE_QUOTE || head->type == SIMPLE_QUOTE)
			process_quotes(token, &j);
		i++;
		j++;
		if (head->next == NULL)
			break ;
		head = head->next;
	}
	head = *token;
	delet_space_fonc(head);
}
