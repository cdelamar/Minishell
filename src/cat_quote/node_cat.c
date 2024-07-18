/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_cat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:43:02 by laubry            #+#    #+#             */
/*   Updated: 2024/07/17 16:55:25 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_head(t_token *head)
{
	free(head->content);
	free(head->next->content);
	free(head->next);
	free(head);
}

int	copy_content(t_token *head, t_token *new_node, int i_content)
{
	while (head->content[i_content])
	{
		new_node->content[i_content] = head->content[i_content];
		i_content++;
	}
	return (i_content);
}

void	before_node_cat(t_token **token, int i)
{
	t_token *head;
	t_token *new_node;
	t_token *before = NULL;
	int	global_len;
	int j;
	int	i_content;

	head = *token;
	new_node = NULL;
	j = 0;
	i_content = 0;
	while (head != NULL && i != 0)
	{
		before = head;
		head = head->next;
		i--;
	}
	global_len = ft_strlen(head->content) + ft_strlen(head->next->content);
	new_node = (t_token *)malloc(sizeof(t_token));
	new_node->content = (char *)malloc(global_len +1);
	i_content = copy_content(head, new_node, i_content);
	while (head->next->content[j])
	{
		if (head->next->content[j] != '"')
		{
			new_node->content[i_content] = head->next->content[j];
			i_content++;
		}
		j++;
	}
	new_node->content[i_content] = '\0';
	new_node->next = head->next->next;
	if (before)
		before->next = new_node;
	else
		*token = new_node;
	free_head(head);
}
