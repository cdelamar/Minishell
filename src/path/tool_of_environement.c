/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_of_environement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:11:13 by laubry            #+#    #+#             */
/*   Updated: 2024/07/10 17:34:11 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_the_dollar(t_token *token)
{
	while (token)
	{
		if (ft_strchr2(token->content, '$') == 1)
			return (token->index);
		token = token->next;
	}
	return (-1);
}

int	skip_prefix(char *word)
{
	int	i;

	i = 0;
	while (word[i] != '$')
		i++;
	return (i +1);
}

char	*skip_sufix(char *word)
{
	int	i;

	i = 1;
	while (word[i] != '"')
		i++;
	word[i] = '\0';
	return (word);
}
