/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:55:09 by laubry            #+#    #+#             */
/*   Updated: 2024/07/22 14:53:27 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	before_node_cat(t_token **token, int i)
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
	i_content = 0;
	advance_to_node(&head, &before, &i);
	global_len = ft_strlen(head->content) + ft_strlen(head->next->content);
	new_node = (t_token *)malloc(sizeof(t_token));
	new_node->content = (char *)malloc(global_len +1);
	new_node->type = 0;
	new_node->index = 0;
	new_node->next = NULL;
	i_content = copy_node(head, new_node, i_content);
	i_content = copy_mid_node(head, new_node, i_content);
	new_node->content[i_content] = '\0';
	new_node->type = WORD;
	if (before)
		before->next = new_node;
	else
		*token = new_node;
	temp = head->next->next;
	new_node->next = temp;
//	new_node->next->next = head->next->next->next;
	free(head->content);
	free(head);
	free(head->next->content);
	free(head->next);
}

void	after_node_cat(t_token **token, int i)
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
	i_content = 0;
	advance_to_node(&head, &before, &i);
	global_len = ft_strlen(head->content) + ft_strlen(head->next->content);
	new_node = (t_token *)malloc(sizeof(t_token));
	new_node->content = (char *)malloc(global_len +1);
	new_node->type = 0;
	new_node->index = 0;
	new_node->next = NULL;
	i_content = copy_mid_after_node(head, new_node, i_content);
	i_content = copy_node_after(head, new_node, i_content);
	new_node->content[i_content] = '\0';
	new_node->type = WORD;
	if (before)
		before->next = new_node;
	else
		*token = new_node;
	temp = head->next->next;
	new_node->next = temp;
//	new_node->next->next = head->next->next->next;
	free(head->content);
	free(head);
	free(head->next->content);
	free(head->next);

}
