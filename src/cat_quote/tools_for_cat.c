/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_cat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:02:15 by laubry            #+#    #+#             */
/*   Updated: 2024/07/21 16:50:59 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_node(t_token *head, t_token *new_node, int i_content)
{
	while (head->content[i_content])
	{
		new_node->content[i_content] = head->content[i_content];
		i_content++;
	}
	return (i_content);
}

int	copy_node_after(t_token *head, t_token *new_node, int i_content)
{
	int	j;

	j = 0;
	if (head->next == NULL || head->next->content == NULL)
		return i_content;
	while (head->next->content[j] != '\0')
	{
		new_node->content[i_content] = head->next->content[j];
		i_content++;
		j++;
	}
	return (i_content);
}

int	copy_mid_node(t_token *head, t_token *new_node, int i_content)
{
	int	j;

	j = 0;
	if (head->next == NULL || head->next->content == NULL)
		return i_content;
	while (head->next->content[j] != '\0')
	{
		if (head->next->content[j] != '"')
		{
			new_node->content[i_content] = head->next->content[j];
			i_content++;
		}
		j++;
	}
	return (i_content);
}

int	copy_mid_after_node(t_token *head, t_token *new_node, int i_content)
{
	int	j;

	j = 0;
	if (head == NULL || head->content == NULL)
		return i_content;
	while (head->content[j] != '\0')
	{
		if (head->content[j] != '"')
		{
			new_node->content[i_content] = head->content[j];
			i_content++;
		}
		j++;
	}
	return (i_content);
}

void	advance_to_node(t_token **head, t_token **before, int *i)
{
	while (*head != NULL && *i > 0)
	{
		*before = *head;
		*head = (*head)->next;
		(*i)--;
	}
}
