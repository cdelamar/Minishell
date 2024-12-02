/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:23:44 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/22 18:29:32 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_new_node(t_token *current)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->type = current->type;
	new_node->content = ft_strdup(current->content);
	if (!new_node->content)
	{
		free(new_node);
		return (NULL);
	}
	new_node->index = current->index;
	new_node->next = NULL;
	return (new_node);
}

t_token	*append_node(t_token **copy_head, t_token **copy_current,
	t_token *new_node)
{
	if (*copy_head == NULL)
	{
		*copy_head = new_node;
		*copy_current = *copy_head;
	}
	else
	{
		(*copy_current)->next = new_node;
		*copy_current = (*copy_current)->next;
	}
	return (*copy_head);
}

t_token	*free_on_error(t_token *copy_head)
{
	free_token_list(copy_head);
	return (NULL);
}

t_token	*copy_token_list(t_token *laubry_list)
{
	t_token	*copy_head;
	t_token	*copy_current;
	t_token	*current;
	t_token	*new_node;

	copy_head = NULL;
	copy_current = NULL;
	current = laubry_list;
	while (current != NULL)
	{
		new_node = create_new_node(current);
		if (!new_node)
			return (free_on_error(copy_head));
		copy_head = append_node(&copy_head, &copy_current, new_node);
		current = current->next;
	}
	return (copy_head);
}
