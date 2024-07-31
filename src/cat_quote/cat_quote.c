/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:58:53 by laubry            #+#    #+#             */
/*   Updated: 2024/07/31 19:51:05 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	side_quote(t_token *token, int place)
{
	t_token	*head;

	head = token;
	if (place < 0)
		return (-1);
	while (place != 0)
	{
		place--;
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

void	delet_space(t_token **token, int place)
{
	t_token	*head;
	t_token	*temp;

	head = *token;
	while (head != NULL && place -1 != 0)
	{
		place--;
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

void	process_quotes(t_token **token, int *place, int verif)
{
	int	boul;

	boul = side_quote(*token, *place -1);
	if (boul == 1 || boul == 2)
	{
		before_node_cat(token, *place -1, verif);
		(*place)--;
	}
	boul = side_quote(*token, *place +1);
	if (boul == 1 || boul == 2)
	{
		if (boul == 2)
			before_node_cat(token, *place, verif);
		else
			after_node_cat(token, *place, verif);
		(*place)--;
	}
}

void	last_verif(t_token **token)
{
	t_token *head;
	int		place;

	place = 0;
	head = *token;
	while (head != NULL)
	{
		if (head->type == LAST_VERIF)
		{
			process_quotes(token, &place, 1);
			//head->type = WORD;
			head = *token;
			place = 0;
		}
		place++;
		head = head->next;
	}
}

void	after_before_cat(t_token **token)
{
	t_token	*head;
	int		place;

	place = 0;
	head = *token;
	while (head != NULL)
	{
		if (head->type == DOUBLE_QUOTE || head->type == SIMPLE_QUOTE)
		{
			process_quotes(token, &place, 0);
			head = *token;
			place = 0;
		}
		place++;
		head = head->next;
	}
	last_verif(token);
	head = *token;
	delet_space_fonc(head);
}
//1"234" 567"89" "0"'12'3
//head->content "
//head->next->content gggg
//head				"

