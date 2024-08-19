/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_of_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:02:27 by laubry            #+#    #+#             */
/*   Updated: 2024/08/19 19:05:13 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_prefix(char *word)
{
	int	i;

	i = 0;
	while (word[i] != '$')
		i++;
	return (i +1);
}

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
