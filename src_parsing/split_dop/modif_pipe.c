/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 23:44:03 by laubry            #+#    #+#             */
/*   Updated: 2024/11/22 18:39:46 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_quote(char **lst, int *i, char quote)
{
	char	*new_str;

	while (lst[*i] && lst[*i][0] != quote)
	{
		if (lst[*i][0] == '|' || lst[*i][0] == '>' || lst[*i][0] == '<')
		{
			new_str = malloc(strlen(lst[*i]) + 2);
			new_str[0] = '\x1F';
			strcpy(new_str + 1, lst[*i]);
			free(lst[*i]);
			lst[*i] = new_str;
		}
		(*i)++;
	}
}

char	**modif_pipe(char **lst)
{
	int		i;
	char	quote;
	int		len;

	i = 0;
	len = 0;
	while (lst[len])
		len++;
	while (lst[i])
	{
		if (lst[i][0] == '"' || lst[i][0] == '\'')
		{
			quote = lst[i++][0];
			process_quote(lst, &i, quote);
		}
		if (i == len)
			return (lst);
		i++;
	}
	return (lst);
}
