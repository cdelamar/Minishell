/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cat_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:41:25 by laubry            #+#    #+#             */
/*   Updated: 2024/08/21 14:10:24 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_node_with_cat(t_token **token_list, char **str, int i)
{
	t_token	*new_node;

	new_node = token_lstnew(str[i]);
	if (new_node == NULL)
		return (check_error(ERROR_NODE));
	new_node->index = i;
	token_lstadd_back(token_list, new_node);
	return (1);
}

void	tab_in_list(t_token **token, char **tab_token)
{
	int	i;

	i = 0;
	while (tab_token[i])
	{
		add_node_with_cat(token, tab_token, i);
		i++;
	}
}

void	quote_sub(t_token **head, char **tab_token, int *i, int *have_quote)
{
	char	quote;

	quote = (*head)->content[0];
	*head = (*head)->next;
	while (*head && (*head)->content[0] != quote)
	{
		tab_token[*i] = ft_strdup_for_quote((*head)->content);
		*head = (*head)->next;
		(*i)++;
	}
	if (*head)
		*head = (*head)->next;
	*have_quote = 1;
}

char	**finalize_tab(char **tab_token, int have_quote, t_token **token)
{
	if (have_quote)
		cat_quote(tab_token, token);
	return (delet_space_to_tab(tab_token));
}

char	**main_cat(t_token **token)
{
	char	**tab_token;
	int		i;
	int		have_quote;
	t_token	*head;

	head = *token;
	have_quote = 0;
	i = 0;
	tab_token = malloc_tab(token);
	while (head != NULL)
	{
		if (head->content[0] == '\'' || head->content[0] == '"')
			quote_sub(&head, tab_token, &i, &have_quote);
		else
		{
			tab_token[i] = ft_strdup(head->content);
			head = head->next;
			i++;
		}
	}
	tab_token[i] = NULL;
	return (finalize_tab(tab_token, have_quote, token));
}
