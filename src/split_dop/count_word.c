/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:34:31 by laubry            #+#    #+#             */
/*   Updated: 2024/07/29 14:55:03 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_char(char s)
{
	if (s == ' ' || s == '"' || s == '\''
		|| s == '|' || s == '<' || s == '>' || s == '\0')
		return (0);
	else
		return (1);
}

int	is_quote(char *s, int i)
{
	char	c;

	c = '\0';
	if (s[i] == '"')
		c = '"';
	else if (s[i] == '\'')
		c = '\'';
	i++;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == '\0')
		return (0);
	i++;
	return (i);
}

int	skip_space(char *s, int i)
{
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	return (i);
}

int	word_plus(char *s, int i, int *tab)
{
	int	word;

	word = 0;
	if (skip_space(s, i) != i)
	{
		i = skip_space(s, i);
		word++;
	}
	else if (s[i] == '|' || s[i] == '>' || s[i] == '<' || s[i] == '\'' || s[i] == '"')
	{
		word++;
		i++;
	}
	tab[0] = i;
	tab[1] += word;
	return (1);
}

size_t	count_word(char *s)
{
	int		tab[3];

	if (s == NULL)
		return (0);
	ft_bzero(tab, 3 * 4);
	while (s[tab[0]])
	{
		if (!is_char(s[tab[0]]))
		{
			if (!word_plus(s, tab[0], tab))
				return (0);
		}
		else if (is_char(s[tab[0]]))
		{
			while (is_char(s[tab[0]]))
				tab[0]++;
			tab[1]++;
		}
		else
			return (0);
	}
	return (tab[1]);
}
