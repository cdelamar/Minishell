/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:33:04 by laubry            #+#    #+#             */
/*   Updated: 2024/07/10 11:02:22 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	count;
	int		in_word;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s == '"')
		{
			s++;
			while (*s && *s != '"')
				s++;
			if (*s == '"')
				s++;
			count++;
			in_word = 0;
		}
		else if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char		**lst;
	size_t		word_len;
	int			i;
	const char	*start;

	lst = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!s || !lst)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			start = s;
			if (*s == '"')
			{
				s++;
				start = s;
				while (*s && *s != '"')
					s++;
				word_len = s - start;
				if (*s == '"')
					s++;
				lst[i++] = ft_substr(start, 0, word_len);
			}
			else
			{
				while (*s && *s != c && *s != '"')
					s++;
				word_len = s - start;
				lst[i++] = ft_substr(start, 0, word_len);
			}
		}
	}
	lst[i] = NULL;
	return (lst);
}
