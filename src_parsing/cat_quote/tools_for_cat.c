/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_cat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:02:15 by laubry            #+#    #+#             */
/*   Updated: 2024/08/19 18:42:12 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_tab(t_token **token)
{
	int		len;
	t_token	*head;

	head = *token;
	len = 0;
	while (head != NULL)
	{
		len++;
		head = head->next;
	}
	return (malloc(sizeof(char *) * (len + 1)));
}

void	cat_quote(char **tab_token, t_token **token)
{
	int	i;
	int	j;
	int	modif;

	i = 0;
	j = 0;
	modif = 0;
	while (tab_token[i])
		i++;
	token_lstclear(token, free);
	while (j != i)
	{
		modif = lstnew_with_cat(tab_token, j);
		j++;
		if (modif > 0)
			j = 0;
	}
}
