/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:55:09 by laubry            #+#    #+#             */
/*   Updated: 2024/07/31 20:09:36 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_old_node(t_token *head)
{
	free(head->content);
	free(head->next->content);
	free(head->next);
	free(head);
}

void	before_node_cat(t_token **token, int i, int verif)
{
	t_token	*head;
	t_token	*new_node;
	t_token	*before;
	t_token *temp;
	int		global_len;
	int		i_content;

	head = *token;
	before = NULL;
	new_node = NULL;
	advance_to_node(&head, &before, &i);
	if (head->content[0] == '\'' || head->content[0] == '"')
		head = head->next;
	global_len = ft_strlen(head->content) + ft_strlen(head->next->content);
	new_node = (t_token *)malloc(sizeof(t_token));
	new_node->content = (char *)malloc(global_len +1);
	new_node->type = 0;
	new_node->index = 0;
	new_node->next = NULL;
	i_content = copy_node(head, new_node);
	i_content = copy_mid_node(head, new_node, i_content);
	new_node->content[i_content] = '\0';
	if (verif == 1)
		new_node->type = WORD;
	else
		new_node->type = LAST_VERIF;
	if (before)
	{
		// if (before->next)
		// {
		// 	free(before->next->content);
		// 	free(before->next);			
		// }
		before->next = new_node;
	}
	else
	{
		t_token *test = *token;
		free(test->content);
		free(test);
		*token = new_node;
	}
	temp = head->next->next;
	new_node->next = temp;
	free_old_node(head);
}

void	after_node_cat(t_token **token, int i, int verif)
{
	t_token	*head;
	t_token	*new_node;
	t_token	*before;
	t_token *temp;
	int		global_len;
	int		i_content;

	head = *token;
	before = NULL;
	new_node = NULL;
	advance_to_node(&head, &before, &i);
	if (head->content[0] == '\'' || head->content[0] == '"')
		head = head->next;
	global_len = ft_strlen(head->content) + ft_strlen(head->next->content);
	new_node = (t_token *)malloc(sizeof(t_token));
	new_node->content = (char *)malloc(global_len +1);
	new_node->type = 0;
	new_node->index = 0;
	new_node->next = NULL;
	i_content = copy_mid_after_node(head, new_node);
	i_content = copy_node_after(head, new_node, i_content);
	new_node->content[i_content] = '\0';
	if (verif == 1)
		new_node->type = WORD;
	else
		new_node->type = LAST_VERIF;
	if (before)
		before->next = new_node;
	else
		*token = new_node;
	temp = head->next->next;
	new_node->next = temp;
	free_old_node(head);
}
