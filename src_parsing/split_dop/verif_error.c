/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:29:33 by laubry            #+#    #+#             */
/*   Updated: 2024/11/05 12:38:03 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	what_quote(char line)
{
	if (line == '"')
		return ('"');
	else
		return ('\'');
}

int	find_end_quote(char **split_line, int *i, char c)
{
	(*i)++;
	while (split_line[*i] && split_line[*i][0] != c)
		(*i)++;
	if (split_line[*i] == NULL)
		return (1);
	return (0);
}

int	solo_quote(char **split_line)
{
	int		i;
	int		quote;
	char	c;

	i = 0;
	quote = 0;
	while (split_line[i])
	{
		if (split_line[i][0] == '\'' || split_line[i][0] == '"')
		{
			c = what_quote(split_line[i][0]);
			if (find_end_quote(split_line, &i, c))
			{
				quote += 1;
				break ;
			}
			quote = 2;
		}
		i++;
	}
	if (quote % 2 == 0)
		return (0);
	else
		return (1);
}

int	if_quotevoid(char **split_line)
{
	if (split_line[0][0] == '"' && split_line[1][0] == '"')
	{
		if (!split_line[2] || !split_line[2][0])
			return (1);
	}
	else if (split_line[0][0] == '\'' && split_line[1][0] == '\'')
	{
		if (!split_line[2] || !split_line[2][0])
			return (1);
	}
	return (0);
}

int	badchar(char **split_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (split_line[i])
	{
		j = 0;
		while (split_line[i][j])
		{
			if (split_line[i][j] == '\x01' || split_line[i][j] == '\x02')
				return (1);
			j++;
		}
		i++;
	}
	if (if_quotevoid(split_line))
		return (1);
	return (0);
}
