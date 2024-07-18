/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_cat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:43:02 by laubry            #+#    #+#             */
/*   Updated: 2024/07/18 05:29:11 by laubry           ###   ########.fr       */
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
	while (head->next->content[j])
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
	while (head->next->content[j])
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
	while (head->content[j])
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

void	before_node_cat(t_token **token, int i)
{
	t_token *head;
	t_token *new_node;
	t_token *before;
	int	global_len;
	int	i_content;

	head = *token;
	before = NULL;
	new_node = NULL;
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
	i_content = copy_node(head, new_node, i_content);
	i_content = copy_mid_node(head, new_node, i_content);
	new_node->content[i_content] = '\0';
	new_node->next = head->next->next;
	if (before)
		before->next = new_node;
	else
		*token = new_node;
	free_head(head);
}

void	after_node_cat(t_token **token, int i)
{
	t_token *head;
	t_token *new_node;
	t_token *before;
	int	global_len;
	int	i_content;

	head = *token;
	before = NULL;
	new_node = NULL;
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
	i_content = copy_mid_after_node(head, new_node, i_content);
	i_content = copy_node_after(head, new_node, i_content);
	new_node->content[i_content] = '\0';
	new_node->type = WORD;
	new_node->next = head->next->next;
	if (before != NULL)
		before->next = new_node;
	else
		*token = new_node;
	free_head(head);
}
