/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_cat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:02:15 by laubry            #+#    #+#             */
/*   Updated: 2024/07/31 08:54:38 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_mid_node(t_token *head, t_token *new_node, int i_content)
{
	int	j;

	j = 0;
	if (head->next == NULL || head->next->content == NULL)
		return i_content;
	while (head->next->content[j] != '\0')
	{
		if (head->next->content[j] != '"' && head->next->content[j] != '\'')
		{
			new_node->content[i_content] = head->next->content[j];
			i_content++;
		}
		j++;
	}
	return (i_content);
}

int	copy_node(t_token *head, t_token *new_node)
{
	int	i;
	int	i_content;

	i = 0;
	i_content = 0;
	if (head->content[i] == '"' || head->content[i] == '\'')
		i++;
	while (head->content[i])
	{
		if (head->content[i] != '"' && head->content[i] !=  '\'')
		{
			new_node->content[i_content] = head->content[i];
			i_content++;
		}
		i++;
	}
	return (i_content);
}

int	copy_mid_after_node(t_token *head, t_token *new_node)
{
	int	j;
	int	i_content;

	j = 0;
	i_content = 0;
	if (head == NULL || head->content == NULL)
		return i_content;
	while (head->content[j] != '\0')
	{
		if (head->content[j] != '"' && head->content[j] != '\'')
		{
			new_node->content[i_content] = head->content[j];
			i_content++;
		}
		j++;
	}
	return (i_content);
}

int	copy_node_after(t_token *head, t_token *new_node, int i_content)
{
	int	j;
//	t_token *temp;

//	temp = head;
	j = 0;
	if (head->next == NULL || head->next->content == NULL)
		return i_content;
	while (head->next->content[j] != '\0')
	{
		new_node->content[i_content] = head->next->content[j];
		i_content++;
		j++;
	}
//	head = temp;
	//i_content = copy_node_after(head, new_node, i_content);		
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
